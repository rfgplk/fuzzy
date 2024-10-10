
//          Copyright David Lucius Severus 2024-.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#pragma once

#include "concepts.hpp"
#include <vector>

#ifdef __SSSE3__
#include <tmmintrin.h>
#endif
#ifdef __SSE4_1__
#include <smmintrin.h>
#endif
#ifdef __AVX2__
#include <immintrin.h>
#endif

namespace fuzzy
{

using lsh_vec = std::vector<int>;

auto
min(int a, int b, int c) -> int
{
  int ab = b ^ ((a ^ b) & -(a < b));
  return c ^ ((ab ^ c) & -(ab < c));
}

template <is_string T>
bool
lsh_prepare_diag(T &a, T &b, lsh_vec &v0, lsh_vec &v1)
{
  size_t a_sz = a.size();
  size_t b_sz = b.size();
  bool fl = false;
  if ( a_sz < b_sz ) {
    std::swap(a, b);
    a_sz = a.size();
    b_sz = b.size();
    fl = true;
  }
  v0.clear();     // to be sure
  v1.clear();
  v0.resize(b.size() + 1, 0);
  v1.resize(b.size() + 1, 0);
  return fl;
}

template <is_string T>
void
lsh_prepare(const T &a, const T &b, lsh_vec &v0, lsh_vec &v1)
{
  size_t a_sz = a.size();
  size_t b_sz = b.size();
  v0.clear();
  v1.clear();
  v0.resize(b.size() + 1, 0);
  v1.resize(b.size() + 1, 0);
}

// TODO: make sure this is accurate for all inputs
// BUG: results vary with extreme inputs
template <is_string T>
int
lsh_diagonal_avx2(T &a, T &b, lsh_vec &v0, lsh_vec &v1)
{

  size_t a_sz = a.size();
  size_t b_sz = b.size();
  for ( size_t i = 0; i <= b_sz; ++i )
    v0[i] = static_cast<int>(i);

  for ( size_t i = 1; i <= a_sz; ++i ) {
    v1[0] = static_cast<int>(i);
    __m256i a_vec = _mm256_set1_epi8(a[i - 1]);
    size_t j = 1;

    for ( ; j + 7 <= b_sz; j += 8 ) {
      __m256i b_vec = _mm256_loadu_si256((__m256i *)(&b[0] + j - 1));
      __m256i cost_vec = _mm256_cmpeq_epi8(a_vec, b_vec);
      cost_vec = _mm256_sub_epi8(_mm256_set1_epi8(1), cost_vec);     // Calculate cost (1 if not equal)

      // Expand 8-bit costs into 32-bit values
      __m256i cost_vec32 = _mm256_cvtepi8_epi32(_mm256_castsi256_si128(cost_vec));     // Low 128-bits of cost_vec

      // Load previous diagonal, top, and left values
      __m256i v0_top = _mm256_loadu_si256((__m256i *)(&v0[0] + j));
      __m256i v0_diag = _mm256_loadu_si256((__m256i *)(&v0[0] + j - 1));
      __m256i v1_rem = _mm256_loadu_si256((__m256i *)(&v1[0] + j - 1));

      // Calculate cost additions
      v0_top = _mm256_add_epi32(v0_top, _mm256_set1_epi32(1));     // v0[j] + 1
      v1_rem = _mm256_add_epi32(v1_rem, _mm256_set1_epi32(1));     // v1[j - 1] + 1
      v0_diag = _mm256_add_epi32(v0_diag, cost_vec32);             // v0[j - 1] + cost

      __m256i res_vec = _mm256_min_epi32(v0_top, v1_rem);     // min(v0[j] + 1, v1[j - 1] + 1)
      res_vec = _mm256_min_epi32(res_vec, v0_diag);           // min(..., v0[j - 1] + cost)

      _mm256_storeu_si256((__m256i *)(&v1[0] + j), res_vec);
    }

    for ( ; j <= b_sz; ++j ) {
      int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
      v1[j] = min(v0[j] + 1, v1[j - 1] + 1, v0[j - 1] + cost);
    }
    std::swap(v0, v1);
  }

  return v0[b_sz];
}

template <is_string T>
int
lsh_avx2(const T &a, const T &b, lsh_vec &a_mat, lsh_vec &b_mat)
{
  size_t a_sz = a.size();
  size_t b_sz = b.size();
  // lsh_vec a_mat(b_sz + 1);
  // lsh_vec b_mat(b_sz + 1);

  for ( size_t j = 0; j <= b_sz; ++j )
    a_mat[j] = j;

  for ( size_t i = 1; i <= a_sz; ++i ) {
    b_mat[0] = i;

    int j = 1;
    __m256i a_vec = _mm256_set1_epi8(a[i - 1]);

    for ( ; j + 31 <= b_sz; j += 32 ) {
      __m256i b_vec = _mm256_loadu_si256((__m256i *)(&b[0] + j - 1));
      __m256i cost_vec = _mm256_cmpeq_epi8(a_vec, b_vec);
      cost_vec = _mm256_sub_epi8(_mm256_set1_epi8(1), cost_vec);

      for ( size_t k = 0; k < 32; ++k ) {
        int cost = ((char *)&cost_vec)[k] & 1;
        b_mat[j + k] = min(a_mat[j + k] + 1, b_mat[j + k - 1] + 1, a_mat[j + k - 1] + cost);
      }
    }

    for ( ; j <= b_sz; ++j ) {
      int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
      b_mat[j] = min(a_mat[j] + 1, b_mat[j - 1] + 1, a_mat[j - 1] + cost);
    }
    std::swap(a_mat, b_mat);
  }
  return a_mat[b_sz];
}
// TODO: add SSE code
template <is_string T>
int
lsh_base(T &a, T &b)
{
  size_t a_sz = a.size();
  size_t b_sz = b.size();

  lsh_vec a_mat(b_sz + 1);
  lsh_vec b_mat(b_sz + 1);

  for ( size_t i = 0; i <= b_sz; i++ )
    a_mat[i] = static_cast<int>(i);

  for ( size_t j = 0; j <= a_sz; j++ ) {
    b_mat[0] = static_cast<int>(j);
    for ( size_t k = 1; k <= b_sz; k++ ) {
      int cost = (a[j - 1] == b[k - 1]) ? 0 : 1;
      b_mat[k] = min(a_mat[k] + 1, b_mat[k - 1] + 1, a_mat[k - 1] + cost);
    }
    std::swap(a_mat, b_mat);
  }
  return a_mat[b_sz];
}
};
