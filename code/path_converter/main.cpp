/**
 * @file main.cpp
 * @author tonghao.yuan (tonghao.yuan@csdental.com)
 * @brief   convert windows path to *nix path
 * @version 0.1
 * @date 2020-05-20
 *
 * @copyright Copyright (c) 2020 Carestream Dental,LLC. All Rights Reserved
 *
 */

// comment this file to run test
#undef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include <utility>

#ifndef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#  define DOCTEST_CONFIG_IMPLEMENT
#endif

#include "docopt/docopt.h"
#include "doctest/doctest.h"

std::string to_unix_string(std::string windows_string) {
  for (auto& c : windows_string) {
    if (c == '\\') {
      c = '/';
    }
  }

  return windows_string;
}

#ifndef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

const auto usage =
  R"(Path converter, convert windows path to *nix path.

  Usage:
    path_converter <path>

  Options:
    -h --help       Show this message
)";

auto main(int argc, char** argv) -> int {
  auto args = docopt::docopt(usage, {argv + 1, argv + argc}, true, "path converter 0.1");

  auto windows_path = args["<path>"];
  std::cout << to_unix_string(args["<path>"].asString()) << std::endl;
}
#endif

using case_type = std::pair<std::string, std::string>;
const auto case_1 = case_type{R"(C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7)",
                              R"(C:/Program Files (x86)/Microsoft Visual Studio 12.0/Common7)"};

const auto case_2 = case_type{R"(C:\Program Files (x86)\Microsoft Visual Studio 12.0\)",
                              R"(C:/Program Files (x86)/Microsoft Visual Studio 12.0/)"};

TEST_CASE("to_unix_string") {
  CHECK(to_unix_string(std::get<0>(case_1)) == std::get<1>(case_1));
  CHECK(to_unix_string(std::get<0>(case_2)) == std::get<1>(case_2));
}