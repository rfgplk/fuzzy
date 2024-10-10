

//          Copyright David Lucius Severus 2024-.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "hamming.hpp"         // for hamming distance
#include "levenshtein.hpp"     // for levenshtein distance

#include <algorithm>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace fuzzy
{

// compare if two strings are similar, and by how much on average (as a %)
// NOTE: for small strings, the percentage will be slightly enlarged due to the padding, although this is entirely
// irrelevant when it comes to comparing strs (the result will be identical) i might get around to fixing this but i was
// too lazy to readjust it, the second pass resolves any conflicts between identicals regardless
template <is_string T>
long double
similar(T &a, T &b)
{
  if ( a.size() == b.size() ) {
    distances_t<int> dists;
    auto f = hamming(a, b, dists);
    return 1.0f - (static_cast<long double>(f) / 64);
  }
  lsh_vec v0, v1;
  bool swapped = lsh_prepare_diag(a, b, v0, v1);
  long double f = 1.0f - static_cast<long double>(lsh_diagonal_avx2(a, b, v0, v1)) / a.size();
  if ( swapped )
    std::swap(a, b);     // TODO: remedy the swap back
  return f;
}

template <is_string T>
long double
metric_hamming(T &a, T &b)
{
  distances_t<int> dists;
  hamming_prepare(a, dists);
  hamming_align(a, b, dists);
  return (static_cast<long double>(arithmean(dists)));
}

template <is_string T>
long double
metric_lsh(T &a, T &b)
{
  lsh_vec v0, v1;
  bool swapped = lsh_prepare_diag(a, b, v0, v1);
  long double f = 1.0f - static_cast<long double>(lsh_diagonal_avx2(a, b, v0, v1)) / a.size();
  if ( swapped )
    std::swap(a, b);     // TODO: remedy the swap back
  return f;
}

template <is_string T>
distances_t<int>
fmetric(T &a, T &b)
{
  distances_t<int> dists;
  hamming_align(a, b, dists);
  return dists;
}

struct pair_result {
  long double res;
  size_t index;
};

// predicate for sort
// TODO: sort (hehe) this out later
bool
pair_sorter_desc(const pair_result &lhs, const pair_result &rhs)
{
  return lhs.res > rhs.res;
}
bool
pair_sorter_ascn(const pair_result &lhs, const pair_result &rhs)
{
  return lhs.res < rhs.res;
}
// fast find
// search for a given token in a list and retrieve the n most similar results
template <is_string T, typename F = std::vector<T>>
inline auto
ffind(T &token, F &lst) -> std::vector<pair_result>
{
  size_t longest = token.size();
  for ( const auto &n : lst ) {
    auto t = n.size();
    if ( t > longest )
      longest = t;
  }
  for ( auto &n : lst )     // pad all to same length of longest
  {
    auto n_sz = n.size();
    for ( size_t i = 0; i < (longest - n_sz); i++ )
      n.insert(n.end(), 0x00);
    n_sz = n.size();
    if ( n_sz % (sizeof(uint64_t) / sizeof(typename T::value_type)) != 0 ) {
      // need to pad
      for ( size_t i = 0; i < (sizeof(uint64_t) - (n_sz % (sizeof(uint64_t) / sizeof(typename T::value_type)))); i++ ) {
        n.insert(n.end(), 0x00);
      }     // pad to fit at least 64bit per round
    }
  }
  auto tk_sz = token.size();
  for ( size_t i = 0; i < (longest - tk_sz); i++ )
    token.insert(token.end(), 0x00);
  size_t n_sz = token.size();
  if ( n_sz % (sizeof(uint64_t) / sizeof(typename T::value_type)) != 0 ) {
    // need to pad
    for ( size_t i = 0; i < (sizeof(uint64_t) - (n_sz % (sizeof(uint64_t) / sizeof(typename T::value_type)))); i++ ) {
      token.insert(token.end(), 0x00);
    }     // pad to fit at least 64bit per round
  }
  std::vector<pair_result> rec(lst.size());
  auto itr = rec.begin();

  for ( auto &n : lst )
    *itr++ = { metric_hamming(token, n), static_cast<size_t>(itr - rec.begin() - 1) };
  // TODO: optimize
  std::sort(rec.begin(), rec.end(), &pair_sorter_ascn);
  return rec;
}

// levenshtein find
// search for a given token in a list and retrieve the n most similar results
template <is_string T, typename F = std::vector<T>>
inline auto
find(T &token, F &lst) -> std::vector<pair_result>
{
  std::vector<pair_result> rec(lst.size());
  auto itr = rec.begin();

  for ( auto &n : lst )
    *itr++ = { metric_lsh(token, n), static_cast<size_t>(itr - rec.begin() - 1) };
  // TODO: optimize
  std::sort(rec.begin(), rec.end(), &pair_sorter_desc);
  return rec;
}

// rough search using hamming distances the strings provided in lst
template <is_string T, typename F = std::vector<T>>
auto
rough_find(T &token, F &lst, const size_t cnt = 0) -> std::vector<pair_result>
{
  if ( cnt ) {
    auto t = ffind(token, lst);
    return std::vector<pair_result>(t.begin(), t.begin() + cnt);
  }
  return ffind(token, lst);
}
// precise search using levenshtein distances the strings provided in lst
template <is_string T, typename F = std::vector<T>>
auto
precise_find(T &token, F &lst, const size_t cnt = 0) -> std::vector<pair_result>
{
  if ( cnt ) {
    auto t = find(token, lst);
    return std::vector<pair_result>(t.begin(), t.begin() + cnt);
  }
  return find(token, lst);
}

template <is_string T> struct fuzzy_result {
  std::vector<T> strings;
  std::vector<pair_result> results;
  T
  operator()(void)
  {
    return strings[results.front().index];
  }
  T
  best_match(void)
  {
    return strings[results.front().index];
  }
  auto
  likelihood(void)
  {
    return results.front().res;
  }
  auto 
  operator[](const size_t n)
  {
    return strings.at(results.at(n));
  }
};

// fuzzy find a token in a list of candidates
template <is_string T, typename F = std::vector<T>>
auto
fuzzy_find(T &token, F &lst, size_t cnt = 0) -> fuzzy_result<T>
{
  auto rtoken = token;
  auto rlst = lst;     // nec since rough_find NULL appends
  if ( cnt > lst.size() )
    cnt = lst.size();
  auto arr = rough_find(
      token, lst,
      0);     // first do a hamming round, if any are <= 1 return the list, enough close hits have been found
  size_t k = 0;
  size_t kl = 0;
  bool fl = false;
  for ( ; k < arr.size(); k++ ) {
    if ( arr[k].res <= 8 )
      kl = k;
    if ( arr[k].res > 8 )
      break;
    if ( arr[k].res > 1 && fl )
      break;
    if ( arr[k].res <= 1 )
      fl = true;

  }     // k - 1 is the last element <= 1
  if ( fl )
    return { rlst, std::vector<pair_result>(arr.begin(), arr.begin() + k) };
  // if not enough hits have been found slice the array into 1/10 and run lsh
  arr = std::vector<pair_result>(arr.begin(), arr.begin() + kl);
  std::vector<T> nv(arr.size());
  size_t i = 0;
  for ( auto &n : arr )
    nv[i++] = rlst[n.index];     // copy only the needed results
  // precise_find will point at nv, return both
  return { nv, precise_find(rtoken, nv, kl > cnt ? cnt : kl) };
}

// check if an identical match exists
template <is_string T, typename F>
bool
fuzzy_exists(T &token, F &lst)
{
  auto arr = rough_find(token, lst, 0);
  for ( const auto &n : arr )
    if ( !n.res )
      return true;
  return false;
}

enum class parse_types { PARSE_ROUGH, PARSE_PRECISE };

};
