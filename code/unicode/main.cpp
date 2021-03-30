#include "fmt/core.h"
#include <iostream>
#include <ostream>
#include <string>

auto print(std::string&& str) {
  fmt::print("{}, {} :\n", str, str.size());
  for (const auto& c : str) {
    fmt::print("{} ", c);
  }
  fmt::print("\n");
  std::flush(std::cout);
}

auto main(int argc, char** argv) -> int {
  constexpr auto ansi = "hello, world";
  constexpr auto unicode = "您好，世界";

  print(ansi);
  print(unicode);

  std::string ss = u8"我";
  // std::wstring ws = u"我";

  std::wcout << "string length : " << ss.length() << std::endl;
  // std::wcout << "wstring length: " << ws.length() << std::endl;

  return 0;
}