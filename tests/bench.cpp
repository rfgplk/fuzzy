
//          Copyright David Lucius Severus 2024-.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

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
  // testing two 1024 char strings against each other for a 1GB bench
  std::string a
      = "QDYcRayphhPeojqekIel1KgiV7WSMZF1BAB9IEgcZPH7gZoNev4MdtK8mgQ7EXubpGiSzKYvOsQX3PXK7IccPN0zsztRGuRHAP4ZE6ZzLCYUzlx"
        "UGBRw8t4Z4rWNbTiYCoC7eWhLyBU4SvNSjnFHQ5NCLpB7J4PI377BhOri59OXGa22LFfCGxnoQhCZaomkxzqIkZBWGojPAfUvQs76eMkQBt959s"
        "2JvTsLim7zraN1r5Nr7Czj4MShB5dBMdTSSDyWrUjO5ASzEkNy0lCYFA7xomZ60HVzs4iEN8yiKZYyzdGxESepURF7F74c4XC0IttU3TfYUvbNG"
        "lrQO9KdMhnj2RIwUT7jcdM2KuQ3oUr48DvsSYlEDdnXN2n22oQVECXxBeaNcsgWC6B9Rph1tBkrHR9IUIJAnNEjhR71NXNpPIDsyy5Mj3kCmPTM"
        "ZiTabwP3CT86IncVdaXqgEvzJxpbRCKlGpsgdt5TqEMzLe7HAnF0XaRkI5YK789mb4LDV6KRI5TjSbkx0NSnelf2vmlmmdVmVvNwVRNUEud7v5Y"
        "E8MadPQgyzmoyUczrqN5tTyyzW3pwvDdpr8NaBhv47XnTovrNJ6gIr4o6sZFGTB4CUMTgq8iWVj0ITQKGZRMMLdR3ntCutKzE0zFFrvQvERHyIU"
        "MvxvnmZ07OjZtBSsAJ0Ulfc2PsyTDlsFyPfprOy2qOAtb2u62taSaMgjX4krc7KlEjP6GmmLkWIEIMAUdpRTakaE8lWgcMnHY55Kf49SZkncgy8"
        "pWdzERQipl3UrpVJmlyJVIHY8ZciDcN852B757nSK1CjBMGY4tzYzdimmiu6Ige14B2L5cYa32fPyYOfIwqj9alpPNhvMil50WXrfCImU087Rl1"
        "NSnut8GvRNNKotNBRRQ4lmnjJIc8vHLrNWZvdkR1zBgBYwuKQwiwNvfNvLfyJJNgNf3MQ0XiZ50GWYSYWHF3pSSAjXR6T8b2tHLfxY6zLCQJBAy"
        "IhOXP02bvgrAvVXsKKogaxCvK";

  std::string b
      = "iYfSzf2yoEVHXUK9PYWl3MEtSlAfRm6tt25nH3r1aGrjQev0pMeyciorRICc3szmfFEDgTPcXQwLcpXqHVGzzSoTJTn7XEBnc0VMFQQfNaVhIe5"
        "AOUcIB1iXC7YbC37CYMKJbkS6MQkdTljDmBNsrvUP2nuUSTjZjiA119uJ7EvZtrDvKx7P91LWCXChnAvcPKlmVkrnl7JR1Fu5jb6Faps6chN7NK"
        "E1W8yqxtbu4AmQiJH6A6NLNamElnkifJWvcKXgn2zAw4TOMdEkf15X1l0JPaXbIQtKE7UuUfQKVtrsTHC9XUlyFwZVbhc0hKY4wPJE4UfsvrmD5"
        "xpjuiiUUA4JisZ2hwFLhTGavg8CXQOaU9niyJLShORkkkG1UY5PqyrdXQ3vJPchAIaJGRoKJrX6iQ7popMJ5PjTEjVBNap7q91vVbR2GqYArV4K"
        "SWSsSSYMFN1bcIXQoDV8YAC3mjzbWQEwFWDIjFOKmSK4M8sVkyJzUMv22GJ0LnarzmhIUgRs5vzJ3AS1Ghm0BvQLzV2TiFPMvrHOScc7T2YuG5Q"
        "WbDC2hoB5X4NgN0YMrBjQvguDzKAHub6IGWPJNBrmVOwvbMndttqz0qINL766uV1n9XZVlUy1ISoxqTsh6Sc5GD7J60sKFmmIOKTYOQLGM2IcZP"
        "xFb2qIbEGimZdpSGysgdgkZ3P8RQOr75scvoaWD9eLd8XFuMIKd0ZohUXRqhwg3hozc79PgLjoLy3fy3DvpuOEWygVn0ceizWPmTJsGVIpYU7da"
        "9E9RpvDihcE5RlqtVejL1Q9IFC5rwVjzEnWZpJxv0uhRX2kvPgV9HS6gSx9U96V9BDfTL6jlYVcqJ4MUmnWmsVfWJosRYvii0s8sQBpPkdFuJ13"
        "8x5UaPNipFbnpmt5bb2RFF1nkYghkFvt4SNJUm2RLOBxxFBPtPFpY3dlKfEmZ3h0C5VS5QDVj2Xbyptuhn0JlnlcKMBdTkclkyTnUYJ4LUwvvSr"
        "e3DdxkFqIBV5A7eTbfLMBtWxS";
  assert(a.size() == 1024 && b.size() == 1024);
  fuzzy::distances_t<int> buf;
  fuzzy::hamming_prepare(a, buf);
  for ( size_t i = 0; i < (size_t)1e7; i++ )
    fuzzy::hamming_align(a, b, buf);
  std::cout << buf[5] << std::endl;
  //~2GB/s
  return 1;
}
