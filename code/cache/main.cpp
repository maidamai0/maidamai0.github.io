#include <array>
#include <iostream>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

constexpr auto cache_size = 3'000;
using MatrixType = std::array<std::array<int, cache_size>, cache_size>;

auto cache() {
  MatrixType matrix{};
  auto counter = 0;
  for (auto i = 0; i < cache_size; ++i) {
    for (auto j = 0; j < cache_size; ++j) {
      matrix[i][j] = counter++;
    }
  }

  ankerl::nanobench::doNotOptimizeAway(counter);
}

auto cache_thrashing() {
  MatrixType matrix{};
  auto counter = 0;
  for (auto i = 0; i < cache_size; ++i) {
    for (auto j = 0; j < cache_size; ++j) {
      matrix[j][i] = counter++;
    }
  }

  ankerl::nanobench::doNotOptimizeAway(counter);
}

auto main(int argc, char** argv) -> int {
  ankerl::nanobench::Bench().run("cache", cache);
  ankerl::nanobench::Bench().run("cache thrashing", cache_thrashing);
}