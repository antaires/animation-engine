#pragma once

const float VEC_EPSILON = 0.000001f;

// the anonymouse union allows Vec3 to be accessed via .x .y .z and
// as a contiguous array using .v
template<typename T>
struct TVec2
{
  union {
    struct {
      T x;
      T y;
    };
    T v[2];
  };
  inline TVec2() : x(0.0f), y(0.0f) {}
  inline TVec2(T _x, T _y):x(_x), y(_y) {}
  inline TVec2(T *fv): x(fv[0]), y(fv[1]) {}
};
typedef TVec2<float> Vec2;
typedef TVec2<int> iVec2;

// basic vector2 operations
Vec2 operator+(const Vec2& a, const Vec2& b);
Vec2 operator-(const Vec2& a, const Vec2& b);
Vec2 operator*(const Vec2& v, float f);
float lenSqr(const Vec2& v);
float len(const Vec2& v);
void normalize(Vec2& v);
Vec2 normalized(const Vec2& v); // return new


struct Vec3
{
  union {
    struct {
      float x;
      float y;
      float z;
    };
    float v[3];
  };
  inline Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
  inline Vec3(float _x, float _y, float _z):x(_x), y(_y), z(_z) {}
  inline Vec3(float *fv): x(fv[0]), y(fv[1]), z(fv[2]) {}
};

// basic vector3 operations
Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& v, float f);
float operator*(const Vec3& a, const Vec3& b);
float operator==(const Vec3& a, const Vec3& b);
float operator!=(const Vec3& a, const Vec3& b);
float dot(const Vec3& a, const Vec3& b);
float lenSqr(const Vec3& v);
float len(const Vec3& v);
void normalize(Vec3& v);       // alters input vec
Vec3 normalized(const Vec3& v); // return new
float angle(const Vec3& a, const Vec3& b);
Vec3 project(const Vec3& a, const Vec3& b);
Vec3 reject(const Vec3& a, const Vec3& b);
Vec3 reflect(const Vec3& a, const Vec3& b);
Vec3 lerp(const Vec3& a, const Vec3& b, float t);
Vec3 slerp(const Vec3& a, const Vec3& b, float t);
Vec3 nlerp(const Vec3& a, const Vec3& b, float t);
