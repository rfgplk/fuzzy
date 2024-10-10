
//          Copyright David Lucius Severus 2024-.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#pragma once
#include <cstdint>
#include <immintrin.h>
#include <unistd.h>

namespace fuzzy
{
int
wegner_pcnt(uint64_t a)
{
  int v = 0;
  while ( a != 0 ) {
    a &= a - 1;
    v++;
  }
  return v;
}

constexpr uint64_t c1 = 0x5555555555555555ULL;
constexpr uint64_t c2 = 0x3333333333333333ULL;
constexpr uint64_t c4 = 0x0F0F0F0F0F0F0F0FULL;
uint64_t
wwg_count(uint64_t x)
{
  x -= (x >> 1) & c1;
  x = ((x >> 2) & c2) + (x & c2);
  x = (x + (x >> 4)) & c4;
  x *= 0x0101010101010101ULL;
  return x >> 56;
}
// 128 bit = 64 x 2
__m128i
popcnt_mula_sse(__m128i v)
{
  __m128i lookup = _mm_setr_epi8(0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
  __m128i low_mask = _mm_set1_epi8(0x0f);
  __m128i lo = _mm_and_si128(v, low_mask);
  __m128i hi = _mm_and_si128(_mm_srli_epi16(v, 4), low_mask);
  __m128i cnt1 = _mm_shuffle_epi8(lookup, lo);
  __m128i cnt2 = _mm_shuffle_epi8(lookup, hi);
  return _mm_add_epi8(cnt1, cnt2);
}


// 256 bit = 64 x 4
__m256i
popcnt_mula_avx2(__m256i v)
{
  __m256i lookup
      = _mm256_setr_epi8(0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
  __m256i low_mask = _mm256_set1_epi8(0x0f);
  __m256i lo = _mm256_and_si256(v, low_mask);
  __m256i hi = _mm256_and_si256(_mm256_srli_epi32(v, 4), low_mask);
  __m256i popcnt1 = _mm256_shuffle_epi8(lookup, lo);
  __m256i popcnt2 = _mm256_shuffle_epi8(lookup, hi);
  __m256i total = _mm256_add_epi8(popcnt1, popcnt2);
  return _mm256_sad_epu8(total, _mm256_setzero_si256());
}

__m256i
popcnt_mula_avx2(uint64_t v1, uint64_t v2, uint64_t v3, uint64_t v4)
{
  __m256i lookup
      = _mm256_setr_epi8(0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
  __m256i low_mask = _mm256_set1_epi8(0x0f);

  __m256i v_vec = _mm256_set_epi64x(v4, v3, v2, v1);     // Load four uint64_t values into __m256i
  __m256i lo = _mm256_and_si256(v_vec, low_mask);
  __m256i hi = _mm256_and_si256(_mm256_srli_epi64(v_vec, 4), low_mask);
  __m256i popcnt1 = _mm256_shuffle_epi8(lookup, lo);
  __m256i popcnt2 = _mm256_shuffle_epi8(lookup, hi);
  __m256i total = _mm256_add_epi8(popcnt1, popcnt2);

  return _mm256_sad_epu8(total, _mm256_setzero_si256());
}

void
CSA(__m256i *h, __m256i *l, __m256i a, __m256i b, __m256i c)
{
  __m256i u = _mm256_xor_si256(a, b);
  *h = _mm256_or_si256(_mm256_and_si256(a, b), _mm256_and_si256(u, c));
  *l = _mm256_xor_si256(u, c);
}

// 256 bit = 64 x 4
uint64_t
popcnt_harvey_seal_avx2(__m256i *d, uint64_t size)
{
  __m256i total = _mm256_setzero_si256();
  __m256i ones = _mm256_setzero_si256();
  __m256i twos = _mm256_setzero_si256();
  __m256i fours = _mm256_setzero_si256();
  __m256i eights = _mm256_setzero_si256();
  __m256i sixteens = _mm256_setzero_si256();
  __m256i twosA, twosB, foursA, foursB, eightsA, eightsB;
  for ( uint64_t i = 0; i < size; i += 16 ) {
    CSA(&twosA, &ones, ones, d[i], d[i + 1]);
    CSA(&twosB, &ones, ones, d[i + 2], d[i + 3]);
    CSA(&foursA, &twos, twos, twosA, twosB);
    CSA(&twosA, &ones, ones, d[i + 4], d[i + 5]);
    CSA(&twosB, &ones, ones, d[i + 6], d[i + 7]);
    CSA(&foursB, &twos, twos, twosA, twosB);
    CSA(&eightsA, &fours, fours, foursA, foursB);
    CSA(&twosA, &ones, ones, d[i + 8], d[i + 9]);
    CSA(&twosB, &ones, ones, d[i + 10], d[i + 11]);
    CSA(&foursA, &twos, twos, twosA, twosB);
    CSA(&twosA, &ones, ones, d[i + 12], d[i + 13]);
    CSA(&twosB, &ones, ones, d[i + 14], d[i + 15]);
    CSA(&foursB, &twos, twos, twosA, twosB);
    CSA(&eightsB, &fours, fours, foursA, foursB);
    CSA(&sixteens, &eights, eights, eightsA, eightsB);
    total = _mm256_add_epi64(total, popcnt_mula_avx2(sixteens));
  }
  total = _mm256_slli_epi64(total, 4);
  total = _mm256_add_epi64(total, _mm256_slli_epi64(popcnt_mula_avx2(eights), 3));
  total = _mm256_add_epi64(total, _mm256_slli_epi64(popcnt_mula_avx2(fours), 2));
  total = _mm256_add_epi64(total, _mm256_slli_epi64(popcnt_mula_avx2(twos), 1));
  total = _mm256_add_epi64(total, popcnt_mula_avx2(ones));
  return _mm256_extract_epi64(total, 0) + _mm256_extract_epi64(total, 1) + _mm256_extract_epi64(total, 2)
         + _mm256_extract_epi64(total, 3);
}

};
