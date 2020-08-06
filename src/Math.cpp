#include "Math.h"
#include <cmath>
#include <iostream>

// macro for matrix mult
#define M4D(aRow, bCol) \
    a.v[0 * 4 + aRow] * b.v[bCol * 4 + 0] + \
    a.v[1 * 4 + aRow] * b.v[bCol * 4 + 1] + \
    a.v[2 * 4 + aRow] * b.v[bCol * 4 + 2] + \
    a.v[3 * 4 + aRow] * b.v[bCol * 4 + 3]

// macro for matrix-vector mult
// performs dot product of row against provided column vec
#define M4V4D(mRow, x, y, z, w) \
    x * m.v[0 * 4 + mRow] + \
    y * m.v[1 * 4 + mRow] + \
    z * m.v[2 * 4 + mRow] + \
    w * m.v[3 * 4 + mRow]

// macro for transpose
#define M4SWAP(x, y) \
    {float t = x; x = y; y = t; }

// macro for inverse of a mat4 to avoid lower order matrices
#define M4_3X3MINOR(x, c0, c1, c2, r0, r1, r2) \
    (x[c0*4*r0] * (x[c1*4+r1] * x[c2*4+r2] - x[c1*4+r2] * \
    x[c2*4+r1]) - x[c1*4+r0]*(x[c0*4+r1] * x[c2*4+r2] -  \
    x[c0*4+r2] * x[c2*4+r1]) + x[c2*4+r0]*(x[c0*4+r1] * \
    x[c1*4+r2] - x[c0*4+r2] * x[c1*4+r1]))

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

bool operator==(const mat4& a, const mat4& b)
{
  for(int i = 0; i < 16; ++i)
  {
    if (std::fabsf(a.v[i] - b.v[i]) > MAT_EPSILON)
    {
      return false;
    }
  }
  return true;
}

mat4 operator+(const mat4& a, const mat4& b)
{
  return mat4(
      a.xx + b.xx, a.xy + b.xy, a.xz + b.xz, a.xw+b.xw
    , a.yx + b.yx, a.yy + b.yy, a.yz + b.yz, a.yw+b.yw
    , a.zx + b.zx, a.zy + b.zy, a.zz + b.zz, a.zw+b.zw
    , a.tx + b.tx, a.ty + b.ty, a.tz + b.tz, a.tw+b.tw
  );
}

mat4 operator*(const mat4& m, float f)
{
  return mat4(
    m.xx * f, m.xy * f, m.xz * f, m.xw * f
    , m.yx * f, m.yy * f, m.yz * f, m.yw * f
    , m.zx * f, m.zy * f, m.zz * f, m.zw * f
    , m.tx * f, m.ty * f, m.tz * f, m.tw * f
  );
}

mat4 operator*(const mat4& a, const mat4& b)
{
  return mat4(
      M4D(0,0), M4D(1,0), M4D(2,0), M4D(3,0)
    , M4D(0,1), M4D(1,1), M4D(2,1), M4D(3,1)
    , M4D(0,2), M4D(1,2), M4D(2,2), M4D(3,2)
    , M4D(0,3), M4D(1,3), M4D(2,3), M4D(3,3)
  );
}

vec4 operator*(const mat4& m, const vec4& v)
{
  return vec4(
      M4V4D(0, v.x, v.y, v.z, v.w)
    , M4V4D(1, v.x, v.y, v.z, v.w)
    , M4V4D(2, v.x, v.y, v.z, v.w)
    , M4V4D(3, v.x, v.y, v.z, v.w)
  );
}

vec3 transformVector(const mat4& m, const vec3& v)
{
  return vec3(
      M4V4D(0, v.x, v.y, v.z, 0.0f)
    , M4V4D(1, v.x, v.y, v.z, 0.0f)
    , M4V4D(2, v.x, v.y, v.z, 0.0f)
  );
}

vec3 transformPoint(const mat4& m, const vec3& v)
{
  return vec3(
      M4V4D(0, v.x, v.y, v.z, 1.0f)
    , M4V4D(1, v.x, v.y, v.z, 1.0f)
    , M4V4D(2, v.x, v.y, v.z, 1.0f)
  );
}

vec3 transformPoint(const mat4& m, const vec3& v, float& w)
{
  // w is a reference to store value for w after execution
  float _w = w;
  w = M4V4D(3, v.x, v.y, v.z, _w);
  return vec3(
      M4V4D(0, v.x, v.y, v.z, _w)
    , M4V4D(1, v.x, v.y, v.z, _w)
    , M4V4D(2, v.x, v.y, v.z, _w)
  );
}

// matrix * its inverse = identity
// thus, view matrix that transforms 3d objs to display onscreen
// is inverse of camera position & rotation

// useful to convert between row-major and column-major matrices
void transpose(mat4& m)
{
  // flip every element of matrix across its main diagonal
  M4SWAP(m.yx, m.xy);
  M4SWAP(m.zx, m.xz);
  M4SWAP(m.tx, m.xw);
  M4SWAP(m.zy, m.yz);
  M4SWAP(m.ty, m.yw);
  M4SWAP(m.tz, m.zw);
}

mat4 transposed(const mat4& m)
{
    return mat4(
        m.xx, m.yx, m.zx, m.tx
      , m.xy, m.yy, m.yz, m.ty
      , m.xz, m.yz, m.zz, m.tz
      , m.xw, m.yw, m.zw, m.tw
    );
}

// determinant : recursive, always a scalar value, only square matrices
// have a determinant.
// * determinant remains the same if matrix transposed
// * minor of a matrix is determinant of some smaller matrix
// * a matrix of minors is a matrix where every element is the minor of the corresponding
// element from the input matrix
// * cofactor matrix : matrix of minors, where every element is mult by -1 to power of (i+J)
// to form a checkerboard matrix of pos(+) and neg(-) whith positive at top left
// Adjugate matrix = transpose of cofactor matrix
// INVERSE = divide adjugate of a matrix by its determinant
float determinant(const mat4& m)
{
  return m.v[0] * M4_3X3MINOR(m.v, 1, 2, 3, 1, 2, 3)
       - m.v[4] * M4_3X3MINOR(m.v, 0, 2, 3, 1, 2, 3)
       + m.v[8] * M4_3X3MINOR(m.v, 0, 1, 3, 1, 2, 3)
       - m.v[12] * M4_3X3MINOR(m.v, 0, 1, 2, 1, 2, 3);
}

mat4 adjugate(const mat4& m)
{
  // cof (M[i,j]) = Minor(M[i,j] * pow(-1, i+j)
  mat4 cofactor;
  cofactor.v[0] =   M4_3X3MINOR(m.v, 1, 2, 3, 1, 2, 3);
  cofactor.v[1] = - M4_3X3MINOR(m.v, 1, 2, 3, 0, 2, 3);
  cofactor.v[2] =   M4_3X3MINOR(m.v, 1, 2, 3, 0, 1, 3);
  cofactor.v[3] = - M4_3X3MINOR(m.v, 1, 2, 3, 0, 1, 2);
  cofactor.v[4] = - M4_3X3MINOR(m.v, 0, 2, 3, 1, 2, 3);
  cofactor.v[5] =   M4_3X3MINOR(m.v, 0, 2, 3, 0, 2, 3);
  cofactor.v[6] = - M4_3X3MINOR(m.v, 0, 2, 3, 0, 1, 3);
  cofactor.v[7] =   M4_3X3MINOR(m.v, 0, 2, 3, 0, 1, 2);
  cofactor.v[8] =   M4_3X3MINOR(m.v, 0, 1, 3, 1, 2, 3);
  cofactor.v[9] = - M4_3X3MINOR(m.v, 0, 1, 3, 0, 2, 3);
  cofactor.v[10] =   M4_3X3MINOR(m.v, 0, 1, 3, 0, 1, 3);
  cofactor.v[11] = - M4_3X3MINOR(m.v, 0, 1, 3, 0, 1, 2);
  cofactor.v[12] = - M4_3X3MINOR(m.v, 0, 1, 2, 1, 2, 3);
  cofactor.v[13] =   M4_3X3MINOR(m.v, 0, 1, 2, 0, 2, 3);
  cofactor.v[14] = - M4_3X3MINOR(m.v, 0, 1, 2, 0, 1, 3);
  cofactor.v[15] =   M4_3X3MINOR(m.v, 0, 1, 2, 0, 1, 2);
  return transposed(cofactor);
}

mat4 inverse(const mat4& m)
{
  float det = determinant(m);
  if (det == 0.0f)
  {
    std::cout<<"\nMatrix determinant is 0";
    return mat4();
  }
  mat4 adj = adjugate(m);
  return adj * (1.0f / det);
}

void invert(mat4& m)
{
  float det = determinant(m);
  if (det == 0.0f)
  {
    std::cout<<"\nMatrix determinant is 0";
    m = mat4();
    return;
  }
  m = adjugate(m) * (1.0f / det);
}
