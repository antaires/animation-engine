#include "Math.h"

// **********************//
//                       //
//   vector2 operations  //
//                       //
// **********************//

Vec2 operator+(const Vec2& a, const Vec2& b)
{
  return Vec2(a.x + b.x, a.y + b.y);
}

Vec2 operator-(const Vec2& a, const Vec2& b)
{
  return Vec2(a.x - b.x, a.y - b.y);
}

Vec2 operator*(const Vec2& v, float f)
{
  return Vec2(v.x * f, v.y * f);
}

// **********************//
//                       //
//   vector3 operations  //
//                       //
// **********************//

Vec3 operator+(const Vec3& a, const Vec3& b)
{
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b)
{
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

// scaling
Vec3 operator*(const Vec3& v, float f)
{
  return Vec3(v.x * f, v.y * f, v.z * f);
}

// dot
float operator*(const Vec3& a, const Vec3& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
