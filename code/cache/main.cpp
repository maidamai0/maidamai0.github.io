#include "vector"
#include <iostream>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

constexpr auto cache_size = 3276;
using MatrixType = std::vector<std::vector<int>>;

auto cache() {
  MatrixType matrix(cache_size, std::vector<int>(cache_size, 0));
  auto counter = 0;
  for (auto i = 0; i < cache_size; ++i) {
    for (auto j = 0; j < cache_size; ++j) {
      matrix[i][j] = counter++;
    }
  }

  ankerl::nanobench::doNotOptimizeAway(counter);
}

auto cache_thrashing() {
  MatrixType matrix(cache_size, std::vector<int>(cache_size, 0));
  auto counter = 0;
  for (auto i = 0; i < cache_size; ++i) {
    for (auto j = 0; j < cache_size; ++j) {
      matrix[j][i] = counter++;
    }
  }

  ankerl::nanobench::doNotOptimizeAway(counter);
}

auto main(int argc, char** argv) -> int {
  ankerl::nanobench::Bench().run("cache thrashing", cache);
  ankerl::nanobench::Bench().run("cache thrashing", cache_thrashing);
}