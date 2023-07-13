#include "vec3d.hpp"

#include <cmath>  // abs, sqrt

namespace Geometry {
Vec3d Vec3d::operator-(const Vec3d &other) const {
  return Vec3d(x - other.x, y - other.y, z - other.z);
}

Vec3d Vec3d::operator-() const { return Vec3d(-x, -y, -z); }

Vec3d Vec3d::operator/(double scalar) const {
  return Vec3d(x / scalar, y / scalar, z / scalar);
};

Vec3d Vec3d::operator+(const Vec3d &other) const {
  return Vec3d(x + other.x, y + other.y, z + other.z);
}

Vec3d Vec3d::operator*(double scalar) const {
  return Vec3d(x * scalar, y * scalar, z * scalar);
}

bool Vec3d::operator==(const Vec3d &other) const {
  return std::abs(x - other.x) <= kEPS && std::abs(y - other.y) <= kEPS &&
         std::abs(z - other.z) <= kEPS;
}

bool Vec3d::operator!=(const Vec3d &other) const { return !(*this == other); }

Vec3d &Vec3d::operator+=(const Vec3d &other) {
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}

Vec3d &Vec3d::operator*=(double scalar) {
  this->x *= scalar;
  this->y *= scalar;
  this->z *= scalar;
  return *this;
}

Vec3d &Vec3d::operator/=(const double value) {
  this->x /= value;
  this->y /= value;
  this->z /= value;
  return *this;
}

double Vec3d::dot_product(const Vec3d &other) const {
  return x * other.x + y * other.y + z * other.z;
};

double Vec3d::distance_to(const Vec3d &other) const {
  return std::sqrt((x - other.x) * (x - other.x) +
                   (y - other.y) * (y - other.y) +
                   (z - other.z) * (z - other.z));
}

double Vec3d::length() const { return std::sqrt(x * x + y * y + z * z); }

Vec3d Vec3d::normalize() const {
  const double length = this->length();
  if (length < kEPS) return kOrigin;
  return *this / length;
}

Vec3d Vec3d::cross_product(const Vec3d &other) const {
  return Vec3d(this->y * other.z - this->z * other.y,
               this->z * other.x - this->x * other.z,
               this->x * other.y - this->y * other.x);
}

Vec3d operator*(double scalar, const Vec3d &point) { return point * scalar; }

}  // namespace Geometry