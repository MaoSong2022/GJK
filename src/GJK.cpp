#include "GJK.hpp"

#include <algorithm>
#include <vector>

namespace GJK {
bool algorithm(Shape *a, Shape *b) {
  const Point origin(0.0, 0.0, 0.0);
  Point d = (a->center() - b->center()).normalize();
  std::vector<Point> simplex;
  simplex.push_back(support(a, b, d));
  d = origin - simplex.front();
  while (true) {
    Point A = support(a, b, d);
    if (A.dot_product(d) < 0) {
      return false;
    }
    simplex.push_back(A);
    if (contains_origin(simplex, d)) {
      return true;
    }
  }
  return true;
};

Point support(Shape *a, Shape *b, const Point &d) {
  return a->support(d) - b->support(-d);
};

Point triple_product(const Point &a, const Point &b, const Point &c) {
  return a.cross_product(b).cross_product(c);
};

bool is_same_direction(const Point &d1, const Point &d2) {
  return d1.dot_product(d2) > 0;
}

bool in_line_segment(const Point &P1, const Point &P2, const Point &Q) {
  if ((Q - P1).cross_product(P2 - P1) == Point(0.0, 0.0, 0.0) &&
      std::min(P1.x, P2.x) <= Q.x && Q.x <= std::max(P1.x, P2.x) &&
      std::min(P1.y, P2.y) <= Q.y && Q.y <= std::max(P1.y, P2.y) &&
      std::min(P1.z, P2.z) <= Q.z && Q.z <= std::max(P1.z, P2.z)) {
    return true;
  }
  return false;
}

bool line_case(std::vector<Point> &simplex, Point &d) {
  const Point &b = simplex[0];
  const Point &a = simplex[1];
  if (in_line_segment(a, b, Point(0.0, 0.0, 0.0))) {
    return true;
  }
  if (is_same_direction(b - a, -a)) {
    d = triple_product(b - a, -a, b - a);
  } else {
    simplex = std::vector<Point>{a};
    d = -a;
  }
  return false;
}

bool contains_origin(std::vector<Point> &simplex, Point &d) {
  const Point o(0.0, 0.0, 0.0);
  if (simplex.size() == 2) {
    return line_case(simplex, d);
  } else {
    // triangle case
    const Point c = simplex[0], b = simplex[1], a = simplex[2];
    const Point ab_perpendicular = triple_product(c - a, b - a, b - a);
    const Point ac_perpendicular = triple_product(b - a, c - a, c - a);
    if (ab_perpendicular.dot_product(o - a) > 0.0) {
      // the origin is in the region AB
      simplex = std::vector<Point>{b, a};
      d = ab_perpendicular;
      return false;
    } else if (ac_perpendicular.dot_product(o - a)) {
      // the origin is in the region AC
      simplex = std::vector<Point>{c, a};
      d = ac_perpendicular;
      return false;
    }
    return true;
  }
};
}  // namespace GJK