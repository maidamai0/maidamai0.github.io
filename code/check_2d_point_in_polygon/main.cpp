/**
 * @file main.cpp
 * @author tonghao.yuan (tonghao.yuan@csdental.com)
 * @brief
 * @ref https://rosettacode.org/wiki/Ray-casting_algorithm#C.2B.2B
 * @version 0.1
 * @date 2020-04-24
 * @copyright Copyright (c) 2020 Carestream Dental,LLC. All Rights Reserved
 *
 */

#include "fmt/core.h"

#include <array>
#include <limits>
#include <numeric>
#include <vcruntime.h>
#include <vector>

#include "time_measure/time_measurement.h"
#include "winding_number.h"

constexpr static size_t g_loop = 10000;

struct Polygon {
  const std::string name;
  const std::vector<Point> edges;
};

class Edge {
public:
  const Point a;
  const Point b;

  auto operator()(const Point& p) const -> bool {
    const auto epsilon = std::numeric_limits<double>::epsilon() * p.y;
    const auto double_min = std::numeric_limits<double>::min();
    const auto double_max = std::numeric_limits<double>::max();

    if (a.y > b.y) {
      return Edge{b, a}(p);
    }

    if (p.y == a.y || p.y == b.y) {
      return operator()({p.x, p.y + epsilon});
    }

    if (p.y > b.y || p.y < a.y || p.x > std::max(a.x, b.x)) {
      return false;
    }

    if (p.x < std::min(a.x, b.x)) {
      return true;
    }

    auto blue = abs(a.x - p.x) > double_min ? (p.y - a.y) / (p.x - a.x) : double_max;
    auto red = abs(a.x - b.x) > double_min ? (b.y - a.y) / (b.x - a.x) : double_max;
    return blue >= red;
  }
};

const std::vector<Point> points
  = {{5.0, 5.0}, {5.0, 8.0}, {-10.0, 5.0}, {0.0, 5.0}, {10.0, 5.0}, {8.0, 5.0}, {10.0, 10.0}};

const Polygon square = {"square", {{0.0, 0.0}, {10.0, 0.0}, {10.0, 10.0}, {0.0, 10.0}}};

const Polygon square_hole
  = {"square_hole",
     {{0.0, 0.0}, {10.0, 0.0}, {10.0, 10.0}, {0.0, 10.0}, {2.5, 2.5}, {7.5, 2.5}, {7.5, 7.5}, {2.5, 7.5}}};

const Polygon strange
  = {"strange", {{0.0, 0.0}, {2.5, 2.5}, {0.0, 10.0}, {2.5, 7.5}, {7.5, 7.5}, {10.0, 10.0}, {10.0, 0}, {2.5, 2.5}}};

const Polygon exagon
  = {"exagon", {{3.0, 0.0}, {7.0, 0.0}, {10.0, 5.0}, {7.0, 10.0}, {3.0, 10.0}, {0.0, 5.0}, {3.0, 0.0}}};

auto check_with_ray_casting(const Point p, const Polygon& polygon) -> bool {
  auto cnt = 0;

  size_t point_index_a = 0;
  size_t point_index_b = polygon.edges.size() - 1;
  for (; point_index_a < polygon.edges.size(); ++point_index_a) {
    const auto point_a = polygon.edges[point_index_a];
    const auto point_b = polygon.edges[point_index_b];
    if (Edge{point_a, point_b}(p)) {
      ++cnt;
    }
    point_index_b = point_index_a;
  }

  return (cnt & 1) != 0;
}

auto measure_cross() {
  BLOCK_MEASURE;
  for (size_t i = 0; i < g_loop; ++i) {
    for (const auto& polygon : {square, square_hole, strange, exagon}) {
      for (const auto& p : points) {
        check_with_ray_casting(p, polygon);
      }
    }
  }
}

auto measure_cross_geomalgorithms_com() {
  BLOCK_MEASURE;
  for (size_t i = 0; i < g_loop; ++i) {
    for (const auto& polygon : {square, square_hole, strange, exagon}) {
      for (const auto& p : points) {
        cross_number(p, polygon.edges);
      }
    }
  }
}

auto measure_widing_geomalgorithms_com() {
  BLOCK_MEASURE;
  for (size_t i = 0; i < g_loop; ++i) {
    for (const auto& polygon : {square, square_hole, strange, exagon}) {
      for (const auto& p : points) {
        winding_number(p, polygon.edges);
      }
    }
  }
}

auto main(int agrc, char** argv) -> int {
  // corectness
  for (const auto& polygon : {square, square_hole, strange, exagon}) {
    for (const auto& p : points) {
      // cross number
      fmt::print("Is Point({},{}) in polygon {}?\n", p.x, p.y, polygon.name);
      fmt::print("Cross number:{}\n", check_with_ray_casting(p, polygon) ? "true" : "false");
      fmt::print("Cross number @geomalgorithms.com:{}\n", cross_number(p, polygon.edges) ? "true" : "false");
      fmt::print("Widing number @geomalgorithms.com:{}\n", winding_number(p, polygon.edges) ? "true" : "false");
    }
  }

  measure_cross();
  measure_cross_geomalgorithms_com();
  measure_widing_geomalgorithms_com();

  // efficiency
}