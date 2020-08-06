#pragma once

const float VEC_EPSILON = 0.000001f;

// the anonymouse union allows vec3 to be accessed via .x .y .z and
// as a contiguous array using .v
template<typename T>
struct Tvec2
{
  union {
    struct {
      T x;
      T y;
    };
    T v[2];
  };
  inline Tvec2() : x(0.0f), y(0.0f) {}
  inline Tvec2(T _x, T _y):x(_x), y(_y) {}
  inline Tvec2(T *fv): x(fv[0]), y(fv[1]) {}
};
typedef Tvec2<float> vec2;
typedef Tvec2<int> ivec2;

// basic vector2 operations
vec2 operator+(const vec2& a, const vec2& b);
vec2 operator-(const vec2& a, const vec2& b);
vec2 operator*(const vec2& v, float f);
float lenSqr(const vec2& v);
float len(const vec2& v);
void normalize(vec2& v);
vec2 normalized(const vec2& v); // return new


struct vec3
{
  union {
    struct {
      float x;
      float y;
      float z;
    };
    float v[3];
  };
  inline vec3() : x(0.0f), y(0.0f), z(0.0f) {}
  inline vec3(float _x, float _y, float _z):x(_x), y(_y), z(_z) {}
  inline vec3(float *fv): x(fv[0]), y(fv[1]), z(fv[2]) {}
};

// basic vector3 operations
vec3 operator+(const vec3& a, const vec3& b);
vec3 operator-(const vec3& a, const vec3& b);
vec3 operator*(const vec3& v, float f);
float operator*(const vec3& a, const vec3& b);
float operator==(const vec3& a, const vec3& b);
float operator!=(const vec3& a, const vec3& b);
float dot(const vec3& a, const vec3& b);
float lenSqr(const vec3& v);
float len(const vec3& v);
void normalize(vec3& v);       // alters input vec
vec3 normalized(const vec3& v); // return new
float angle(const vec3& a, const vec3& b);
vec3 project(const vec3& a, const vec3& b);
vec3 reject(const vec3& a, const vec3& b);
vec3 reflect(const vec3& a, const vec3& b);
vec3 lerp(const vec3& a, const vec3& b, float t);
vec3 slerp(const vec3& a, const vec3& b, float t);
vec3 nlerp(const vec3& a, const vec3& b, float t);

template<typename T>
struct Tvec4
{
  union {
    struct {
      T x;
      T y;
      T z;
      T w;
    };
    T v[4];
  };
  inline Tvec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
  inline Tvec4(T _x, T _y, T _z, T _w):x(_x), y(_y), z(_z), w(_w) {}
  inline Tvec4(T *fv): x(fv[0]), y(fv[1]), z(fv[2]), w(fv[3]) {}
};
typedef Tvec4<float> vec4;
typedef Tvec4<int> ivec4;

// **********************//
//                       //
//      MATRIX           //
//                       //
// **********************//
// NOTE: uses column-major matrices
// A E I M
// B F J N
// C G K O
// D H L P
// but represented as a linear array
// thus mapping func is different: column * numberOfRows + row

struct mat4
{
  union {
    float v[16];
    struct {
      // each variable represents a column, named after basis vector of that column
      vec4 right;
      vec4 up;
      vec4 forward;
      vec4 position;
    };
    struct {
      // access elements by basis vector - first letter == basis vec and 2nd letter == component of that vec
      // column 1
      float xx;
      float xy;
      float xz;
      float xw;
      // column 2
      float yx;
      float yy;
      float yz;
      float yw;
      // column 3
      float zx;
      float zy;
      float zz;
      float zw;
      // column 4
      float tx;
      float ty;
      float tz;
      float tw;
    };
    struct {
      // access using column-row notation
      float c0r0;
      float c0r1;
      float c0r2;
      float c0r3;
      float c1r0;
      float c1r1;
      float c1r2;
      float c1r3;
      float c2r0;
      float c2r1;
      float c2r2;
      float c2r3;
      float c3r0;
      float c3r1;
      float c3r2;
      float c3r3;
    };
    struct {
      // access using row-column notation
      float r0c0;
      float r1c0;
      float r2c0;
      float r3c0;
      float r0c1;
      float r1c1;
      float r2c1;
      float r3c1;
      float r0c2;
      float r1c2;
      float r2c2;
      float r3c2;
      float r0c3;
      float r1c3;
      float r2c3;
      float r3c3;
    };
  };

  // create identity matrix
  inline mat4() : xx(1), xy(0), xz(0), xw(0)
                , yx(0), yy(1), yz(0), yw(0)
                , zx(0), zy(0), zz(1), zw(0)
                , tx(0), ty(0), tz(0), tw(1)
                {}

  // create from float array
  inline mat4(float *fv) : xx(fv[0]),  xy(fv[1]),  xz(fv[2]),  xw(fv[3])
                         , yx(fv[4]),  yy(fv[5]),  yz(fv[6]),  yw(fv[7])
                         , zx(fv[8]),  zy(fv[9]),  zz(fv[10]), zw(fv[11])
                         , tx(fv[12]), ty(fv[13]), tz(fv[14]), tw(fv[15])
                         {}

  // create from each element
  inline mat4(float _00, float _01, float _02, float _03
            , float _10, float _11, float _12, float _13
            , float _20, float _21, float _22, float _23
            , float _30, float _31, float _32, float _33)
            : xx(_00), xy(_01), xz(_02), xw(_03)
            , yx(_10), yy(_11), yz(_12), yw(_13)
            , zx(_20), zy(_21), zz(_22), zw(_23)
            , tx(_30), ty(_31), tz(_32), tw(_33) 
            {}
};
