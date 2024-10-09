#include "../src/hamming.hpp"
#include "../src/levenshtein.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

template <typename T, typename F>
void
splat(const T &a, const T& b, F f)
{
  std::cout << "The difference between " << a << " and " << b << " was: " << f << std::endl;
}

int
main(void)
{
  fuzzy::distances_t<int> dists;
  long double f = 0.0f;
  std::string a = "Hello!";
  std::string b = "Hello!";
  f = fuzzy::hamming(a, b, dists);
  dists.clear();
  splat(a, b, f);
  assert(f == 0.0f);
  std::string c = "Testing";
  std::string d = "Testinc";
  f = fuzzy::hamming(c, d, dists);
  dists.clear();
  splat(c, d, f);
  assert(f == 1.0f);
  std::string tca = "Three Chars were Different!";
  std::string tcb = "Thr333Chars were Different!";
  f = fuzzy::hamming(tca, tcb, dists);
  dists.clear();
  splat(tca, tcb, f);
  assert(f == 2.75f);
  std::string sh = "A not so quite short string.";
  std::string lg = "A really really long string!";
  f = fuzzy::hamming(sh, lg, dists);
  dists.clear();
  splat(sh, lg, f);
  std::string lng =  "This string is incredibly long this time! Look at how long it is! Almost a novel!";
  std::string shrt = "This is a short string, which isn't a novel. Look at how short it is! Wow! Wow!!!";
  f = fuzzy::hamming(lng, shrt, dists);
  dists.clear();
  splat(lng, shrt, f);
  std::string x = "Kite";
  std::string y = "Kitten";
  auto i = fuzzy::lsh_base(x, y);
  splat(x, y, i);
  
  return 1;
};
