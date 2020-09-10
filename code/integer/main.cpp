#include "fmt/core.h"
#include <cstdio>
#include <iostream>
#include <istream>
#include <limits>
#include <vector>

// #include "doctest/doctest.h"

auto main() -> int {
  char c = std::numeric_limits<char>::min();

  for (int i = 0; i < 300; ++i) {
    // fmt::print("c is {}\n", c);

    std::cout << "c is " << c << std::endl;
    ++c;
  }
  std::flush(std::cout);
  return 0;
}