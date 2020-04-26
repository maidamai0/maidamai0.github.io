#pragma once

/**
 * @brief implementation of winding number function
 * @ref http://geomalgorithms.com/a03-_inclusion.html
 *
 */

// Copyright 2000 softSurfer, 2012 Dan Sunday
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.

#include <vector>

struct Point {
  double x = 0.0;
  double y = 0.0;
};

/**
 * @brief tests if a point is Left|On|Right of an infinite line.
 *
 * @param P0  one point of line
 * @param P1  the other point of line
 * @param P2  point to check
 * @return    >0 for P2 left of the line through P0 and P1
 *            =0 for P2  on the line
 *            <0 for P2  right of the line
 * @see       Algorithm 1 "Area of Triangles and Polygons"
 */
inline auto is_left(Point P0, Point P1, Point P2) -> double {
  return ((P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y));
}

/**
 * @brief           crossing number test for a point in a polygon
 *
 * @param point     a point  to be checked
 * @param vertices  vertex points of a polygon vertice
 * @return true     @ref point is in polygon
 * @return false    @ref point is out of polygon
 */
auto cross_number(const Point& point, const std::vector<Point>& vertices) -> bool {
  int cn = 0; // the  crossing number counter

  size_t start = 0;
  size_t end = vertices.size() - 1;
  // loop through all edges of the polygon
  for (; start < vertices.size(); start++) {                                  // edge from vertices[i]  to vertices[i+1]
    if (((vertices[start].y <= point.y) && (vertices[end].y > point.y))       // an upward crossing
        || ((vertices[start].y > point.y) && (vertices[end].y <= point.y))) { // a downward crossing
      // compute the actual edge-ray intersect x-coordinate
      const auto vt = (point.y - vertices[start].y) / (vertices[end].y - vertices[start].y);
      if (point.x < vertices[start].x + vt * (vertices[end].x - vertices[start].x)) // check_point.x < intersect
        ++cn; // a valid crossing of y=P.y right of P.x
    }
    end = start;
  }
  return (cn & 1) == 1; // 0 if even (out), and 1 if  odd (in)
}

/**
 * @brief           winding number test for a point in a polygon
 *
 * @param point     a point  to be checked
 * @param vertices  vertex points of a polygon vertice
 * @return true     @ref point is in polygon
 * @return false    @ref point is out of polygon
 */
auto winding_number(const Point& point, const std::vector<Point>& vertices) -> bool {
  int wn = 0; // the  winding number counter

  size_t start = 0;
  size_t end = vertices.size() - 1;
  // loop through all edges of the polygon
  for (; start < vertices.size(); ++start) {                      // edge from vertices[i] to  vertices[i+1]
    if (vertices[start].y <= point.y) {                           // start y <= P.y
      if (vertices[end].y > point.y) {                            // an upward crossing
        if (is_left(vertices[start], vertices[end], point) > 0) { // P left of  edge
          ++wn;
        }
      }                                                           // have  a valid up intersect
    } else {                                                      // start y > P.y (no test needed)
      if (vertices[end].y <= point.y) {                           // a downward crossing
        if (is_left(vertices[start], vertices[end], point) < 0) { // P right of  edge
          --wn;                                                   // have  a valid down intersect
        }
      }
    }
    end = start;
  }
  return wn != 0;
}