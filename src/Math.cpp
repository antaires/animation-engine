#include "Math.h"
#include <cmath>

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

float lenSqr(const Vec2& v)
{
  return (v.x * v.x) + (v.y * v.y);
}
float len(const Vec2& v)
{
  float lenSq = (v.x * v.x) + (v.y * v.y);
  if (lenSq < VEC_EPSILON)
  {
    return 0.0f;
  }
  return std::sqrtf(lenSq);
}

void normalize(Vec2& v)
{
  float lenSq = (v.x * v.x) + (v.y * v.y);
  if (lenSq < VEC_EPSILON)
  {
    return;
  }
  float invLen = 1.0f / std::sqrtf(lenSq);
  v.x *= invLen;
  v.y *= invLen;
}

Vec2 normalized(const Vec2& v)
{
  float lenSq = (v.x * v.x) + (v.y * v.y);
  if (lenSq < VEC_EPSILON)
  {
    return v;
  }
  float invLen = 1.0f / std::sqrtf(lenSq);
  return Vec2(v.x * invLen, v.y * invLen);
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

float lenSqr(const Vec3& v)
{
  return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

float len(const Vec3& v)
{
  float lenSq = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
  if (lenSq < VEC_EPSILON)
  {
    return 0.0f;
  }
  return std::sqrtf(lenSq);
}

void normalize(Vec3& v)
{
  float lenSq = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
  if (lenSq < VEC_EPSILON)
  {
    return;
  }
  float invLen = 1.0f / std::sqrtf(lenSq);
  v.x *= invLen;
  v.y *= invLen;
  v.z *= invLen;
}

Vec3 normalized(const Vec3& v)
{
  float lenSq = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
  if (lenSq < VEC_EPSILON)
  {
    return v;
  }
  float invLen = 1.0f / std::sqrtf(lenSq);
  return Vec3(v.x * invLen, v.y * invLen, v.z * invLen);
}

float angle(const Vec3& a, const Vec3& b)
{
  float aLenSq = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
  float bLenSq = (b.x * b.x) + (b.y * b.y) + (b.z * b.z);

  if (aLenSq < VEC_EPSILON || bLenSq < VEC_EPSILON)
  {
    return 0.0f;
  }

  float dot = a.x * b.x + a.y * b.y + a.z * b.z;

  acosf(dot / (std::sqrtf(aLenSq) * std::sqrtf(bLenSq)));
}
