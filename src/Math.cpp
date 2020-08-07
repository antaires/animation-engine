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

// ***************** //
// camera functions  //
// ***************** //

mat4 frustum(float l, float r, float b, float t, float n, float f)
{
  if( l == r || t == b || n == f )
  {
    std::cout<<"\nInvalid frustum";
    return mat4();
  }
  return mat4(
    (2.0f * n) / (r - 1), 0, 0, 0
    , 0, (2.0f * n) / (t - b), 0, 0
    , (r+l)/(r-l), (t+b)/(t-b), (-(f+n))/(f-n), -1
    , 0, 0, (-2*f*n) / (f-n), 0
  );
}

mat4 perspective(float fov, float aspect, float n, float f)
{
  float ymax = n * std::tanf(fov * 3.14159265359f / 360.0f);
  float xmax = ymax * aspect;
  return frustum(-xmax, xmax, -ymax, ymax, n, f);
}

// for 2d or isometric games
mat4 ortho(float l, float r, float b, float t, float n, float f)
{
  if( l == r || t == b || n == f )
  {
    std::cout<<"\nInvalid ortho";
    return mat4();
  }
  return mat4(
    2.0f / (r-l), 0, 0, 0
    , 0, 2.0f / (t-b), 0, 0
    , 0, 0, -2.0f / (f-n), 0
    , -((r+l)/(r-l)), -((t+b)/(t-b)), -((f+n)/(f-n)), 1
  );
}

// construct a view matrix
mat4 lookAt(const vec3& position, const vec3& target, const vec3& up)
{
  vec3 f = normalized(target - position) * -1.0f;
  vec3 r = cross(up, f);
  // right handed
  if (r == vec3(0, 0, 0))
  {
    std::cout<<"\nError in lookAt";
    return mat4();
  }
  normalize(r);
  vec3 u = normalized(cross(f, r));
  // right handed
  vec3 t = vec3(
    -dot(r, position)
    , -dot(u, position)
    , -dot(f, position)
  );
  return mat4(
    // transpose upper 3x3 matrix to invert it
      r.x, u.x, f.x, 0
    , r.y, u.y, f.y, 0
    , r.z, u.z, f.z, 0
    , t.x, t.y, t.z, 1
  );
}


// **********************//
//                       //
//      Quaternions      //
//                       //
// **********************//

quat angleAxis(float angle, const vec3& axis)
{
  vec3 norm = normalized(axis);
  // divide by 2 to map quat range to sin/cos
  // since quat has a period of 720 degrees
  // and sin/cos has period of 360 degrees
  float s = std::sinf(angle * 0.5f);
  return quat(
      norm.x * s
    , norm.y * s
    , norm.z * s
    , std::cosf(angle * 0.5f)
  );
}

quat fromTo(const vec3& from, const vec3& to)
{
  // normalize and makes sure they are not the same vector
  vec3 f = normalized(from);
  vec3 t = normalized(to);
  if (f == t){return quat();}

  // check whether vecs are opposite each other
  // if yes, most orthogonal axis of FROM vec
  // can be used to create pure quaternion
  else if (f == t * -1.0f)
  {
    vec3 ortho = vec3(1, 0, 0);
    if (std::fabsf(f.y) < std::fabsf(f.x))
    {
      ortho = vec3(0, 1, 0);
    }
    if (std::fabsf(f.z) < std::fabs(f.y) && std::fabs(f.z) < std::fabsf(f.x))
    {
      ortho = vec3(0, 0, 1);
    }
    vec3 axis = normalized(cross(f, ortho));
    return quat(axis.x, axis.y, axis.z, 0);
  }

  // create a half vec between FROM and TO vecs
  // use cross prod of half vec and starting vec to calc
  // axis of rotation and the dot product to find
  // angle of rotation
  vec3 half = normalized(f + t);
  vec3 axis = cross(f, half);
  return quat(
      axis.x
    , axis.y
    , axis.z
    , dot(f, half)
  );
}

vec3 getAxis(const quat& quat)
{
  return normalized(vec3(quat.x, quat.y, quat.z));
}

float getAngle(const quat& quat)
{
  return 2.0f * std::acosf(quat.w);
}

quat operator+(const quat& a, const quat& b)
{
  return quat(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

quat operator-(const quat& a, const quat& b)
{
  return quat(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

quat operator*(const quat& a, float b)
{
  return quat(a.x * b, a.y * b, a.z * b, a.w * b);
}

quat operator-(const quat& a)
{
  return quat(-a.x, -a.y, -a.z, -a.w);
}

// a quaternion and its inverse rotate to the SAME SPOT
// but take different routes
bool operator==(const quat& left, const quat& right)
{
  return (std::fabsf(left.x - right.x) <= QUAT_EPSILON
       && std::fabsf(left.y - right.y) <= QUAT_EPSILON
       && std::fabsf(left.z - right.z) <= QUAT_EPSILON
       && std::fabsf(left.w - right.w) <= QUAT_EPSILON);
}

bool operator!=(const quat& a, const quat& b)
{
  return !(a==b);
}

bool sameOrientation(const quat& a, const quat& b)
{
  return (std::fabsf(a.x - b.x) <= QUAT_EPSILON
       && std::fabsf(a.y - b.y) <= QUAT_EPSILON
       && std::fabsf(a.z - b.z) <= QUAT_EPSILON
       && std::fabsf(a.w - b.w) <= QUAT_EPSILON)
       ||
         (std::fabsf(a.x + b.x) <= QUAT_EPSILON
       && std::fabsf(a.y + b.y) <= QUAT_EPSILON
       && std::fabsf(a.z + b.y) <= QUAT_EPSILON
       && std::fabsf(a.w + b.w) <= QUAT_EPSILON);
}

// like vectors, dot prod. measures how similar 2 quats are
float dot(const quat& a, const quat& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// like vectors, squared length is same as dot product of quat with itself
// the length of a quat is the square root of the square length
float lenSq(const quat& q)
{
  return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

float len(const quat& q)
{
  float lenSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
  if (lenSq < QUAT_EPSILON)
  {
    return 0.0f;
  }
  return std::sqrtf(lenSq);
}

// unit quaternions have a length of 1
// quats representing a rotation should always be unit quats
void normalize(quat& q)
{
  float lenSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
  if (lenSq < QUAT_EPSILON)
  {
    return;
  }
  // inverse length
  float i_len = 1.0f / std::sqrtf(lenSq);
  q.x *= i_len;
  q.y *= i_len;
  q.z *= i_len;
  q.w *= i_len;
}

quat normalized(const quat& q)
{
  float lenSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
  if (lenSq < QUAT_EPSILON)
  {
    return quat();
  }
  float i_len = 1.0f / std::sqrtf(lenSq);
  return quat(q.x * i_len
            , q.y * i_len
            , q.z * i_len
            , q.w * i_len);
}

// inverse of a normalized quat is the conjugate
// the conjugate of a quat flips its axis of rotation
// to check if a quat is normalized: the squared length
// of a normalized quat is ALWAYS == 1
quat conjugate(const quat& q)
{
  return quat(
      -q.x
    , -q.y
    , -q.z
    , q.w
  );
}

// proper quat inverse is the conjugate divdied by
// squared length of the quat
quat inverse(const quat& q)
{
  float lenSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
  if (lenSq < QUAT_EPSILON)
  {
    return quat();
  }
  float recip = 1.0f / lenSq;
  return quat(-q.x * recip
            , -q.y * recip
            , -q.z * recip
            , q.w * recip);
}

// mult opperation carried out right to left:
// the right quats rotation is applied first, then the left
quat operator*(const quat& q1, const quat& q2)
{
  return quat(
      q2.x*q1.w + q2.y*q1.z - q2.z*q1.y + q2.w*q1.x
    , -q2.x*q1.z + q2.w*q1.x + q2.z*q1.x + q2.w*q1.y
    , q2.x*q1.y - q2.y*q1.x + q2.z*q1.w + q2.w*q1.z
    , -q2.x*q1.x - q2.y*q1.y - q2.z*q1.z + q2.w*q1.w
  );
}

// to mult a vec & quats, need to turn the vec
// into a PURE quat, which is a quat where w = 0
// and the vec part is normalized
// the mult always yeilds vector that's rotated by the quat
vec3 operator*(const quat& q, const vec3& v)
{
  return q.vector * 2.0f * dot(q.vector, v)
    + v * (q.scalar * q.scalar - dot(q.vector, q.vector))
    + cross(q.vector, v) * 2.0f * q.scalar;
}

// interpolation
// quats are a rotation, not an orientation
// every rotation can take long or short arc, with
// short being best usually. to pick shortest,
// neighborhooding is used to place quats in desired neighborhood
// if dot product of quats is +, shorter will be taken
// if -, longer will be taken (so negate 1 of the quats)
// to get shorter :
//if(dot(a,b) < 0.0f) b = -b;

// this is like a lerp, but not because it travels in an arc
// assumes both quats in desired neighborhood
quat mix(const quat& from, const quat& to, float t)
{
    return from * (1.0f - t) + to * t;
}

// nlerp is a fast & good approx for spherical interpolation
// assumes both quats in desired neighborhood
quat nlerp(const quat& from, const quat& to, float t)
{
  return normalized(from + (to - from) * t);
}

// to adjust angle of a quaternion, raise it to
// desired power. example: to adjust quat to only
// rotate halfway, raise to power of 0.5
// to raise a quat to a power, decompose quat into angle
// and an axis, then angle can be adjusted by power
// and a new quat built from the adjusted angle & axis
quat operator^(const quat& q, float f)
{
  float angle = 2.0f * std::acosf(q.scalar);
  vec3 axis = normalized(q.vector);
  float halfCos = std::cosf(f * angle * 0.5f);
  float halfSin = std::sinf(f * angle * 0.5f);
  return quat(
      axis.x * halfSin
    , axis.y * halfSin
    , axis.z * halfSin
    , halfCos
  );
}

// slerp - only use if consistent velocity required
// if back and end quats are close together, use nlerp
// // assumes both quats in desired neighborhood
quat slerp(const quat& start, const quat& end, float t)
{
    if(std::fabsf(dot(start, end)) > 1.0f - QUAT_EPSILON)
    {
      return nlerp(start, end, t);
    }
    // could use conjugate instead of inverse since
    // input vecs to slerp SHOULD BE NORMALIZED
    quat delta = inverse(start) * end;
    return normalized((delta ^ t) * start);
}

// rotation to lookAt
quat lookRotation(const vec3& direction, const vec3& up)
{
  // find orthonormal basis vectors:
  // object Forward
  vec3 f = normalized(direction);
  // desired up
  vec3 u = normalized(up);
  // right
  vec3 r = cross(u, f);
  // object up
  u = cross(f, r);

  // from world forward to object forward
  quat worldToObject = fromTo(vec3(0, 0, 1), f);

  // what direction is the new object up?
  vec3 objectUp = worldToObject * vec3(0, 1, 0);

  // from object up to desired up
  quat u2u = fromTo(objectUp, u);

  // rotate to forward direction first
  // then twist to correct up
  quat result = worldToObject * u2u;

  return normalized(result);
}

// quat to mat4, simply mult world basis vectors
// (x, y, & z world axes) by the quat & store the
// results in the components of the matrix, in which
// 1st column is right vec
// 2nd column is up vec
// 3rd column is forward vec
mat4 quatToMat4(const quat& q)
{
    vec3 r = q * vec3(1, 0, 0);
    vec3 u = q * vec3(0, 1, 0);
    vec3 f = q * vec3(0, 0, 1);
    return mat4(
        r.x, r.y, r.z, 0
      , u.x, u.y, u.z, 0
      , f.x, f.y, f.z, 0
      , 0  , 0  , 0  , 1
    );
}

// a matrix stores both rotation and scale data
// using same components, so need to normalize basis
// vectors and the cross product needs to be used to
// make sure vecs are orthogonal
quat mat4ToQuat(const mat4& m)
{
  vec3 up = normalized(vec3(m.up.x, m.up.y, m.up.z));
  vec3 forward = normalized(vec3(m.forward.x, m.forward.y, m.forward.z));
  vec3 right = cross(up, forward);

  up = cross(forward, right);
  return lookRotation(forward, up);
}
