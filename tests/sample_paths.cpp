

#include "../src/fuzzy.hpp"
#include <iostream>

#include <string>

int
main(void)
{
  {
    std::string to_find = "lude/sche";
    std::string str1 = "~/data/photos/holidays/";
    std::string str2 = "/bin/ulimit";
    std::string str3 = "/usr/include/c++/14/filesystem";
    std::string str4 = "/usr/include/sched.h";
    std::string str5 = "/mnt/drivea/usr/include/sched.h";
    std::cout << "1: Strings '" << to_find << "' and '" << str1 << "' are " << fuzzy::similar(to_find, str1) * 100
              << "% similar" << std::endl;
    std::cout << "2: Strings '" << to_find << "' and '" << str2 << "' are " << fuzzy::similar(to_find, str2) * 100
              << "% similar" << std::endl;
    std::cout << "3: Strings '" << to_find << "' and '" << str3 << "' are " << fuzzy::similar(to_find, str3) * 100
              << "% similar" << std::endl;
    std::cout << "4: Strings '" << to_find << "' and '" << str4 << "' are " << fuzzy::similar(to_find, str4) * 100
              << "% similar" << std::endl;
    std::cout << "5: Strings '" << to_find << "' and '" << str5 << "' are " << fuzzy::similar(to_find, str5) * 100
              << "% similar" << std::endl;
  }
  {
    std::string to_find = "include/sched";
    std::string str1 = "~/data/photos/holidays/";
    std::string str2 = "/bin/ulimit";
    std::string str3 = "/usr/include/c++/14/filesystem";
    std::string str4 = "/usr/include/sched.h";
    std::string str5 = "/mnt/drivea/usr/include/sched.h";
    std::cout << "1: Strings '" << to_find << "' and '" << str1 << "' are " << fuzzy::similar(to_find, str1) * 100
              << "% similar" << std::endl;
    std::cout << "2: Strings '" << to_find << "' and '" << str2 << "' are " << fuzzy::similar(to_find, str2) * 100
              << "% similar" << std::endl;
    std::cout << "3: Strings '" << to_find << "' and '" << str3 << "' are " << fuzzy::similar(to_find, str3) * 100
              << "% similar" << std::endl;
    std::cout << "4: Strings '" << to_find << "' and '" << str4 << "' are " << fuzzy::similar(to_find, str4) * 100
              << "% similar" << std::endl;
    std::cout << "5: Strings '" << to_find << "' and '" << str5 << "' are " << fuzzy::similar(to_find, str5) * 100
              << "% similar" << std::endl;
  }
  {
    std::string to_find = "/usr/include/sched.h";
    std::string str1 = "~/data/photos/holidays/";
    std::string str2 = "/bin/ulimit";
    std::string str3 = "/usr/include/c++/14/filesystem";
    std::string str4 = "/usr/include/sched.h";
    std::string str5 = "/mnt/drivea/usr/include/sched.h";
    std::cout << "1: Strings '" << to_find << "' and '" << str1 << "' are " << fuzzy::similar(to_find, str1) * 100
              << "% similar" << std::endl;
    std::cout << "2: Strings '" << to_find << "' and '" << str2 << "' are " << fuzzy::similar(to_find, str2) * 100
              << "% similar" << std::endl;
    std::cout << "3: Strings '" << to_find << "' and '" << str3 << "' are " << fuzzy::similar(to_find, str3) * 100
              << "% similar" << std::endl;
    std::cout << "4: Strings '" << to_find << "' and '" << str4 << "' are " << fuzzy::similar(to_find, str4) * 100
              << "% similar" << std::endl;
    std::cout << "5: Strings '" << to_find << "' and '" << str5 << "' are " << fuzzy::similar(to_find, str5) * 100
              << "% similar" << std::endl;
  }
  return 0;
}
