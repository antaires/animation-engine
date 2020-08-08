#include "Transform.h"
#include <cmath>


// a transform maps from one space to another
// combining transforms mantains a right-to-left order
// SCALE - ROTATE - TRANSLATE
// combining scale and rotation is easy: multiply
// combining position is harder, bc pos needs to be affected
// by rotation and scale
Transform combine(const Transform& a, Transform& b)
{
  Transform out;
  out.scale = a.scale * b.scale;
  out.rotation = a.rotation * b.rotation;
  out.position = a.rotation * (a.scale*b.position);
  out.position = a.position + out.position;
  return out;
}

//a reverse of the transform, map the transform back into the
// original space
// for scale, remember that 0 can't be inverted
Transform inverse(const Transform& t)
{
  Transform inv;

  inv.rotation = inverse(t.rotation);
  inv.scale.x = std::fabs(t.scale.x) < VEC_EPSILON ? 0.0f : 1.0f / t.scale.x;
  inv.scale.y = std::fabs(t.scale.y) < VEC_EPSILON ? 0.0f : 1.0f / t.scale.y;
  inv.scale.z = std::fabs(t.scale.z) < VEC_EPSILON ? 0.0f : 1.0f / t.scale.z;

  vec3 invTrans = t.position * -1.0f;
  inv.position = inv.rotation * (inv.scale * invTrans);

  return inv;
}


// interpolation : blend / mix transforms
// linearly interpolate the positoin, rotation and scale
Transform mix(const Transform& a, const Transform& b, float t)
{
    quat bRot = b.rotation;
    if (dot(a.rotation, bRot) < 0.0f)
    {
      bRot = -bRot;
    }

    vec3 pos = lerp(a.position, b.position, t);
    quat rot = nlerp(a.rotation, bRot, t);
    vec3 sca = lerp(a.scale, b.scale, t);

    return Transform(
        pos
      , rot
      , sca
    );
}

// converting transforms to matrices
// used to send data to shaders
mat4 transformToMat4(const Transform& t)
{
    // extract the rotation basis of the transform
    vec3 x = t.rotation * vec3(1, 0, 0);
    vec3 y = t.rotation * vec3(0, 1, 0);
    vec3 z = t.rotation * vec3(0, 0, 1);

    // scale the basis the vectors
    x = x * t.scale.x;
    y = y * t.scale.y;
    z = z * t.scale.z;

    // extract the position of the transform
    vec3 p = t.position;

    // create matrix
    return mat4(
        x.x, x.y, x.z, 0 // X basis & scale
      , y.x, y.y, y.z, 0 // Y basis & scale
      , z.x, z.y, z.z, 0 // Z basis & scale
      , p.x, p.y, p.z, 1 // position
    );
}

// mat to transfrom is scale lossy (might contain skew data)
// which makes it inaccurate
Transform mat4ToTransform(const mat4& m)
{
  Transform out;

  out.position = vec3(m.v[12], m.v[13], m.v[14]);
  out.rotation = mat4ToQuat(m);

  mat4 rotScaleMat(
      m.v[0], m.v[1], m.v[2] , 0
    , m.v[4], m.v[5], m.v[6] , 0
    , m.v[8], m.v[9], m.v[10], 0
    , 0     , 0     , 0      , 1
  );
  mat4 invRotMat = quatToMat4(inverse(out.rotation));
  mat4 scaleSkewMat = rotScaleMat * invRotMat;
  out.scale = vec3(
      scaleSkewMat.v[0]
    , scaleSkewMat.v[5]
    , scaleSkewMat.v[10]
  );

  return out;
}

// use a transform to move a point or vector in space
vec3 transformPoint(const Transform& a, const vec3& b)
{
  vec3 out;
  out = a.rotation * (a.scale * b);
  out = a.position + out;
  return out;
}

vec3 transformVector(const Transform&a, const vec3& b)
{
  vec3 out;
  out = a.rotation * (a.scale * b);
  return out;
}
