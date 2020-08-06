#include "Math.h"
#include <cmath>

// **********************//
//                       //
//   vector2 operations  //
//                       //
// **********************//

vec2 operator+(const vec2& a, const vec2& b)
{
  return vec2(a.x + b.x, a.y + b.y);
}

vec2 operator-(const vec2& a, const vec2& b)
{
  return vec2(a.x - b.x, a.y - b.y);
}

vec2 operator*(const vec2& v, float f)
{
  return vec2(v.x * f, v.y * f);
}

float lenSqr(const vec2& v)
{
  return (v.x * v.x) + (v.y * v.y);
}
float len(const vec2& v)
{
  float lenSq = (v.x * v.x) + (v.y * v.y);
  if (lenSq < VEC_EPSILON)
  {
    return 0.0f;
  }
  return std::sqrtf(lenSq);
}

void normalize(vec2& v)
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

vec2 normalized(const vec2& v)
{
  float lenSq = (v.x * v.x) + (v.y * v.y);
  if (lenSq < VEC_EPSILON)
  {
    return v;
  }
  float invLen = 1.0f / std::sqrtf(lenSq);
  return vec2(v.x * invLen, v.y * invLen);
}

// **********************//
//                       //
//   vector3 operations  //
//                       //
// **********************//

vec3 operator+(const vec3& a, const vec3& b)
{
  return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec3 operator-(const vec3& a, const vec3& b)
{
  return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

// scaling
vec3 operator*(const vec3& v, float f)
{
  return vec3(v.x * f, v.y * f, v.z * f);
}

// dot
float operator*(const vec3& a, const vec3& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

float operator==(const vec3& a, const vec3& b)
{
    vec3 diff(a - b);
    return lenSqr(diff) < VEC_EPSILON;
}

float operator!=(const vec3& a, const vec3& b)
{
  return !(a == b);
}

float dot(const vec3& a, const vec3& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

float lenSqr(const vec3& v)
{
  return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

float len(const vec3& v)
{
  float lenSq = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
  if (lenSq < VEC_EPSILON)
  {
    return 0.0f;
  }
  return std::sqrtf(lenSq);
}

void normalize(vec3& v)
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

vec3 normalized(const vec3& v)
{
  float lenSq = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
  if (lenSq < VEC_EPSILON)
  {
    return v;
  }
  float invLen = 1.0f / std::sqrtf(lenSq);
  return vec3(v.x * invLen, v.y * invLen, v.z * invLen);
}

float angle(const vec3& a, const vec3& b)
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
vec3 project(const vec3& a, const vec3& b)
{
  // a dot b divided by len b
  float bLen = len(b);
  if (bLen < VEC_EPSILON)
  {
    return vec3();
  }
  float scale = dot(a, b) / bLen;
  return b * scale;
}

vec3 reject(const vec3& a, const vec3& b)
{
  vec3 projection = project(a, b);
  return a - projection;
}

// bounce reflection, where a 'bounces' off of
// plane and b is the plane's normal
vec3 reflect(const vec3& a, const vec3& b)
{
  float bLen = len(b);
  if(bLen < VEC_EPSILON)
  {
    return vec3();
  }
  float scale = dot(a, b) / bLen;
  vec3 projection2 = b * (scale * 2);
  return a - projection2;
}

vec3 cross(const vec3& a, const vec3& b)
{
  return vec3(
    a.y * b.z - a.z * b.y
    , a.z * b.x - a.x * b.z
    , a.x * b.y - a.y * b.x
  );
}

vec3 lerp(const vec3& s, const vec3& e, float t)
{
  // straight line (so lenght is not constant in relation to t)
  // always takes the shortest path from one vec to another
  return vec3(
    s.x + (e.x - s.x) * t
    , s.y + (e.y - s.y) * t
    , s.z + (e.z - s.z) * t
  );
}

vec3 slerp(const vec3& s, const vec3& e, float t)
{
  // arc between two vectors
  if (t < 0.01f)
  {
    return lerp(s, e, t);
  }

  vec3 from = normalized(s);
  vec3 to   = normalized(e);
  float theta = angle(from, to);
  float sin_theta = sinf(theta);
  float a = sinf((1.0f - t) * theta) / sin_theta;
  float b = sinf(t * theta) / sin_theta;
  return from * a + to * b;
}

vec3 nlerp(const vec3& s, const vec3& e, float t)
{
  // approximates slerp, but isn't constant velocity
  // faster to compute
  vec3 linear(
    s.x + (e.x - s.x) * t
    , s.y + (e.y - s.y) * t
    , s.z + (e.z - s.z) * t
  );
  return normalized(linear);
}


// **********************//
//                       //
//   Matrix operations   //
//                       //
// **********************//
