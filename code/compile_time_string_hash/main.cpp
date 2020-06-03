/**
 * @file main.cpp
 * @author tonghao.yuan (tonghao.yuan@csdental.com)
 * @brief compile time string hash
 * @details see
 *              https://stackoverflow.com/questions/2111667/compile-time-string-hashing/2112111#2112111
 *              https://stackoverflow.com/questions/37658794/integer-constant-overflow-warning-in-constexpr
 *      for detail
 * @version 0.1
 * @date 2020-06-03
 *
 */

#include <iostream>
#include <string>
#include <vector>

constexpr auto hashFnv1b(const char* s, unsigned int fnv1a_basis = 0x811c9dc5, unsigned int fnv1a_prime = 0x01000193)
  -> unsigned int {
  return *s == 0
           ? fnv1a_basis
           : hashFnv1b(s + 1,
                       static_cast<unsigned int>((fnv1a_basis ^ *s) * static_cast<unsigned long long>(fnv1a_prime)));
}

void test(std::string key_str) {
  const auto key = hashFnv1b(key_str.c_str());
  switch (key) {
    case hashFnv1b("first"): {
      std::cout << "first" << std::endl;
      break;
    }
    case hashFnv1b("second"): {
      std::cout << "second" << std::endl;
      break;
    }
    case hashFnv1b("third"): {
      std::cout << "third" << std::endl;
      break;
    }
    case hashFnv1b("fourth"): {
      std::cout << "fourth" << std::endl;
      break;
    }
    default: {
      std::cout << "default" << std::endl;
    }
  }
}

auto main() -> int {
  std::vector<std::string> ss{"first", "second", "third", "fourth"};
  for (const auto& s : ss) {
    test(s);
  }

  return 0;
}
