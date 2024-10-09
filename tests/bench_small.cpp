#include "../src/hamming.hpp"

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
  fuzzy::distances_t<int> buf;
  fuzzy::hamming_prepare(a, buf);
  for ( size_t i = 0; i < (size_t)1e9; i++ )
    fuzzy::hamming_align(a, b, buf);
  std::cout << buf[5] << std::endl;
  //~2GB/s
  return 1;
}
