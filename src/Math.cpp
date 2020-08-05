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

float operator==(const Vec3& a, const Vec3& b)
{
    Vec3 diff(a - b);
    return lenSqr(diff) < VEC_EPSILON;
}

float operator!=(const Vec3& a, const Vec3& b)
{
  return !(a == b);
}

float dot(const Vec3& a, const Vec3& b)
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

// project a onto b (get part of a in direction of b)
Vec3 project(const Vec3& a, const Vec3& b)
{
  // a dot b divided by len b
  float bLen = len(b);
  if (bLen < VEC_EPSILON)
  {
    return Vec3();
  }
  float scale = dot(a, b) / bLen;
  return b * scale;
}

Vec3 reject(const Vec3& a, const Vec3& b)
{
  Vec3 projection = project(a, b);
  return a - projection;
}

// bounce reflection, where a 'bounces' off of
// plane and b is the plane's normal
Vec3 reflect(const Vec3& a, const Vec3& b)
{
  float bLen = len(b);
  if(bLen < VEC_EPSILON)
  {
    return Vec3();
  }
  float scale = dot(a, b) / bLen;
  Vec3 projection2 = b * (scale * 2);
  return a - projection2;
}

Vec3 cross(const Vec3& a, const Vec3& b)
{
  return Vec3(
    a.y * b.z - a.z * b.y
    , a.z * b.x - a.x * b.z
    , a.x * b.y - a.y * b.x
  );
}

Vec3 lerp(const Vec3& s, const Vec3& e, float t)
{
  // straight line (so lenght is not constant in relation to t)
  // always takes the shortest path from one vec to another
  return Vec3(
    s.x + (e.x - s.x) * t
    , s.y + (e.y - s.y) * t
    , s.z + (e.z - s.z) * t
  );
}

Vec3 slerp(const Vec3& s, const Vec3& e, float t)
{
  // arc between two vectors
  if (t < 0.01f)
  {
    return lerp(s, e, t);
  }

  Vec3 from = normalized(s);
  Vec3 to   = normalized(e);
  float theta = angle(from, to);
  float sin_theta = sinf(theta);
  float a = sinf((1.0f - t) * theta) / sin_theta;
  float b = sinf(t * theta) / sin_theta;
  return from * a + to * b;
}

Vec3 nlerp(const Vec3& s, const Vec3& e, float t)
{
  // approximates slerp, but isn't constant velocity
  // faster to compute
  Vec3 linear(
    s.x + (e.x - s.x) * t
    , s.y + (e.y - s.y) * t
    , s.z + (e.z - s.z) * t
  );
  return normalized(linear);
}
