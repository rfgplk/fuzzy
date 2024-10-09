

#include "../src/fuzzy.hpp"
#include <iostream>

#include <string>

int
main(void)
{
  std::string str1 = "compression_base.hpp";
  std::string str2 = "compress.h";
  std::string str3 = "camera_handler.js";
  std::string str4 = "files_base.py";
  std::string str5 = "comp_class.cpp";
  std::cout << "Strings '" << str1 << "' and '" << str2 << "' are " << fuzzy::similar(str1, str2) * 100 << "% similar"
            << std::endl;
  std::cout << "Strings '" << str1 << "' and '" << str3 << "' are " << fuzzy::similar(str2, str3) * 100 << "% similar"
            << std::endl;
  std::cout << "Strings '" << str1 << "' and '" << str4 << "' are " << fuzzy::similar(str3, str4) * 100 << "% similar"
            << std::endl;
  std::cout << "Strings '" << str1 << "' and '" << str5 << "' are " << fuzzy::similar(str1, str5) * 100 << "% similar"
            << std::endl;
  return 0;
}
