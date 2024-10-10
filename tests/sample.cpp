
//          Copyright David Lucius Severus 2024-.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "../src/fuzzy.hpp"
#include <iostream>

#include <string>

int
main(void)
{
  std::string str1 = "Hello World!";
  std::string str2 = "Hello World?";
  std::string str3 = "hello world!";
  std::string str4 = "cat";
  std::string str5 = "/";
  std::string str10
      = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse quis leo sed ante interdum feugiat eu vel "
        "ante. Aenean volutpat risus eget tincidunt mollis. Donec sit amet elementum lorem. Sed elementum, risus id "
        "sagittis egestas, magna dolor pellentesque enim, in cursus tortor mauris ac quam. Morbi ligula odio, tincidunt "
        "vel faucibus eu, rhoncus quis lacus. Aliquam ac nulla eros. In hac habitasse platea dictumst. Nam laoreet, "
        "purus porta facilisis viverra, elit est auctor ex, quis vehicula mauris odio vitae sapien.      Duis eros "
        "libero,      luctus quis urna nec,      bibendum consequat neque.Sed sed ipsum sit amet erat porta "
        "auctor.Pellentesque mattis eget augue ac scelerisque.Etiam vel auctor velit.In augue sapien,      bibendum at "
        "molestie et,       sollicitudin id leo.Donec pellentesque metus quis purus facilisis          "
        "consequat.Curabitur lobortis ante eget tempus egestas.Donec congue,      nibh sit amet euismod consequat, "
        "mauris orci hendrerit ligula, at accumsan enim dui id lacus.Nam eu erat feugiat,      vehicula leo vel, "
        "molestie ligula.Nunc eget dignissim libero,      eu volutpat neque.Sed gravida sagittis libero vel "
        "consequat.Mauris mollis sollicitudin          hendrerit.Maecenas imperdiet varius vulputate.Morbi dignissim "
        "vestibulum mauris,      sit amet vulputate justo fringilla maximus.Nullam massa tortor, suscipit vitae metus "
        "et,      sodales viverra leo.Aliquam ac risus quis odio sodales tincidunt.";
  std::string str11 = "meow";
  std::cout << "Strings '" << str1 << "' and '" << str2 << "' are " << fuzzy::similar(str1, str2) * 100 << "% similar"
            << std::endl;
  std::cout << "Strings '" << str2 << "' and '" << str3 << "' are " << fuzzy::similar(str2, str3) * 100 << "% similar"
            << std::endl;
  std::cout << "Strings '" << str3 << "' and '" << str4 << "' are " << fuzzy::similar(str3, str4) * 100 << "% similar"
            << std::endl;
  std::cout << "Strings '" << str1 << "' and '" << str5 << "' are " << fuzzy::similar(str1, str5) * 100 << "% similar"
            << std::endl;
  std::cout << "Strings '" << str10 << "' and '" << str11 << "' are " << fuzzy::similar(str10, str11) * 100
            << "% similar" << std::endl;
  return 0;
}
