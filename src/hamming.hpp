#pragma once

#include "concepts.hpp"
#include "popcnts.hpp"

#include <cstdint>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>


namespace fuzzy
{
template <typename T>
inline __attribute__((always_inline)) long double
harmonicmean(const std::vector<T> &src)
{
  long double recsum = 0.0f;
  for ( size_t i = 0; i < src.size(); i++ )
    recsum += (1 / static_cast<long double>(src[i]));
  return static_cast<long double>(src.size()) / recsum;
}

template <typename T>
inline __attribute__((always_inline)) long double
arithmean(const std::vector<T> &src)
{
  long double sum = 0.0f;
  if ( src.size() >= 4 )
    for ( size_t i = 0; i < src.size(); i += 4 ) {
      sum += src[i];
      sum += src[i + 1];
      sum += src[i + 2];
      sum += src[i + 3];
    }
  else {
    for ( size_t i = 0; i < src.size(); i++ ) {
      sum += src[i];
    }
  }
  //   sum += n;
  return src.empty() ? 0.0f : static_cast<long double>(sum / src.size());
}

template <typename T> using distances_t = std::vector<T>;

template <is_string T>
void
hamming_prepare(const T &t, distances_t<int> &dists)
{
  const size_t sz = t.size() / (sizeof(uint64_t) / sizeof(typename T::value_type));     // size in 64bit
  dists.resize(sz, 0);
}
#if defined __has_builtin
#if __has_builtin(__builtin_popcountll)

template <is_string T>
void
hamming_align(T &a, T &b, distances_t<int> &dists)
{
  const auto sz_a = a.size();
  const auto sz_b = b.size();
  if ( sz_a % (sizeof(uint64_t) / sizeof(typename T::value_type)) != 0 ) {
    // need to pad
    for ( size_t i = 0; i < (sizeof(uint64_t) - (sz_a % (sizeof(uint64_t) / sizeof(typename T::value_type)))); i++ ) {
      a.insert(a.end(), 0x00);
    }     // pad to fit at least 64bit per round
  }
  if ( sz_a < sz_b ) {
    for ( size_t i = 0; i < sz_b - sz_a; i++ ) {
      a.insert(a.end(), 0x00);
    }     // pad to fit at least 64bit per round
  }
  if ( sz_b % (sizeof(uint64_t) / sizeof(typename T::value_type)) != 0 ) {
    // need to pad
    for ( size_t i = 0; i < (sizeof(uint64_t) - (sz_b % (sizeof(uint64_t) / sizeof(typename T::value_type)))); i++ ) {
      b.insert(b.end(), 0x00);
    }     // pad to fit at least 64bit per round
  }
  if ( sz_b < sz_a ) {
    for ( size_t i = 0; i < sz_a - sz_b; i++ ) {
      b.insert(b.end(), 0x00);
    }     // pad to fit at least 64bit per round
  }

  const size_t sz = a.size() / (sizeof(uint64_t) / sizeof(typename T::value_type));     // size in 64bit
  dists.resize(sz, 0);
  const uint64_t *a_ptr = reinterpret_cast<const uint64_t *>(a.data());
  const uint64_t *b_ptr = reinterpret_cast<const uint64_t *>(b.data());
  if ( sz % 4 == 0 ) [[likely]]
    for ( size_t i = 0; i < sz; i += 4 ) {
      dists[i] = __builtin_popcountll(a_ptr[i] ^ b_ptr[i]);
      dists[i + 1] = __builtin_popcountll(a_ptr[i + 1] ^ b_ptr[i + 1]);
      dists[i + 2] = __builtin_popcountll(a_ptr[i + 2] ^ b_ptr[i + 2]);
      dists[i + 3] = __builtin_popcountll(a_ptr[i + 3] ^ b_ptr[i + 3]);
    }
  else
    for ( size_t i = 0; i < sz; i++ )
      dists[i] = __builtin_popcountll(a_ptr[i] ^ b_ptr[i]);
}

template <is_string T>
void
hamming_align_np(T &a, T &b, distances_t<int> &dists)
{
  const auto sz_a = a.size();
  const auto sz_b = b.size();
  if ( sz_a % (sizeof(uint64_t) / sizeof(typename T::value_type)) != 0 ) {
    // need to pad
    for ( size_t i = 0; i < (sizeof(uint64_t) - (sz_a % (sizeof(uint64_t) / sizeof(typename T::value_type)))); i++ ) {
      a.insert(a.end(), 0x00);
    }     // pad to fit at least 64bit per round
  }
  if ( sz_a < sz_b ) {
    for ( size_t i = 0; i < sz_b - sz_a; i++ ) {
      a.insert(a.end(), 0x00);
    }     // pad to fit at least 64bit per round
  }
  if ( sz_b % (sizeof(uint64_t) / sizeof(typename T::value_type)) != 0 ) {
    // need to pad
    for ( size_t i = 0; i < (sizeof(uint64_t) - (sz_b % (sizeof(uint64_t) / sizeof(typename T::value_type)))); i++ ) {
      b.insert(b.end(), 0x00);
    }     // pad to fit at least 64bit per round
  }
  if ( sz_b < sz_a ) {
    for ( size_t i = 0; i < sz_a - sz_b; i++ ) {
      b.insert(b.end(), 0x00);
    }     // pad to fit at least 64bit per round
  }

  const size_t sz = a.size() / (sizeof(uint64_t) / sizeof(typename T::value_type));     // size in 64bit
  const uint64_t *a_ptr = reinterpret_cast<const uint64_t *>(a.data());
  const uint64_t *b_ptr = reinterpret_cast<const uint64_t *>(b.data());
  if ( sz % 4 == 0 ) [[likely]]
    for ( size_t i = 0; i < sz; i += 4 ) {
      dists[i] = __builtin_popcountll(a_ptr[i] ^ b_ptr[i]);
      dists[i + 1] = __builtin_popcountll(a_ptr[i + 1] ^ b_ptr[i + 1]);
      dists[i + 2] = __builtin_popcountll(a_ptr[i + 2] ^ b_ptr[i + 2]);
      dists[i + 3] = __builtin_popcountll(a_ptr[i + 3] ^ b_ptr[i + 3]);
    }
  else
    for ( size_t i = 0; i < sz; i++ )
      dists[i] = __builtin_popcountll(a_ptr[i] ^ b_ptr[i]);
}

template <is_string T>
long double
hamming(T &a, T &b, distances_t<int> &dists)
{
  const auto sz_a = a.size();
  const auto sz_b = b.size();
  if ( sz_a == sz_b ) [[likely]] {     // original design. of the alg for equal sizes

    if ( sz_a % (sizeof(uint64_t) / sizeof(typename T::value_type)) != 0 ) {
      // need to pad
      for ( size_t i = 0; i < (sizeof(uint64_t) - (sz_a % (sizeof(uint64_t) / sizeof(typename T::value_type)))); i++ ) {
        a.insert(a.end(), 0x00);
        b.insert(b.end(), 0x00);
      }     // pad to fit at least 64bit per round
    }

    const size_t sz = a.size() / (sizeof(uint64_t) / sizeof(typename T::value_type));     // size in 64bit
    dists.resize(sz, 0);
    const uint64_t *a_ptr = reinterpret_cast<const uint64_t *>(a.data());
    const uint64_t *b_ptr = reinterpret_cast<const uint64_t *>(b.data());
    for ( size_t i = 0; i < sz; i++ )
      dists[i] = __builtin_popcountll(a_ptr[i] ^ b_ptr[i]);
    return arithmean(dists);
  }
  return -1.0f;
}
#else
template <is_string T>
long double
hamming(T &a, T &b, distances_t<uint64_t> &dists)
{
  const auto sz_a = a.size();
  const auto sz_b = b.size();
  if ( sz_a == sz_b ) {     // original design. of the alg for equal sizes

    if ( sz_a % (sizeof(uint64_t) / sizeof(typename T::value_type)) != 0 ) {
      // need to pad
      for ( size_t i = 0; i < (sizeof(uint64_t) - (sz_a % (sizeof(uint64_t) / sizeof(typename T::value_type)))); i++ ) {
        a.insert(a.end(), 0x00);
        b.insert(b.end(), 0x00);
      }     // pad to fit at least 64bit per round
    }

    const size_t sz = a.size() / (sizeof(uint64_t) / sizeof(typename T::value_type));     // size in 64bit
    dists.resize(sz, 0);
    const uint64_t *a_ptr = reinterpret_cast<const uint64_t *>(a.data());
    const uint64_t *b_ptr = reinterpret_cast<const uint64_t *>(b.data());
    for ( size_t i = 0; i < sz; i++ )
      dists[i] = wwg_count(a_ptr[i] ^ b_ptr[i]);
    return arithmean(dists);
  }
  return -1.0f;
}
#endif
#endif
};
