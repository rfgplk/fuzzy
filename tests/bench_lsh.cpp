
//          Copyright David Lucius Severus 2024-.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#include "../src/hamming.hpp"
#include "../src/levenshtein.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

template <typename T, typename F>
void
splat(const T &a, const T &b, F f)
{
  std::cout << "The difference between " << a << " and " << b << " was: " << f << std::endl;
}

int
main(void)
{
  // testing two 1024 char strings against each other for a 1GB bench
  std::string a = "Dogsa89034534390868953489bc";

  std::string b = "89345636890";
  volatile int x = 0;
  std::vector<int> v0;
  std::vector<int> v1;
  fuzzy::lsh_prepare_diag(a, b, v0, v1);
  for ( size_t i = 0; i < (size_t)1e8; i++ )
    x = fuzzy::lsh_diagonal_avx2(a, b, v0, v1);
  std::cout << x << std::endl;
  return 1;
}
