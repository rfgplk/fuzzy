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
  // testing two 8 char strings against each other for a 8GB bench
  std::string a = "crusting";
  std::string b = "crusting";

  assert(a.size() == 8 && b.size() == 8);
  fuzzy::lsh_vec v0, v1;
  fuzzy::lsh_prepare_diag(a, b, v0, v1);
  for ( size_t i = 0; i < (size_t)1e9; i++ )
    fuzzy::lsh_diagonal_avx2(a, b, v0, v1);
  //~133MB/s
  return 1;
}
