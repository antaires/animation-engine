#include "Track.h"
#include <cmath>

template Track<float, 1>;
template Track<vec3, 3>;
template Track<quat, 4>;

namespace TrackHelpers
{
  inline float Interpolate(float a, float b, float t){return a + (b - a) * t;}

  inline vec3 Interpolate(const vec3& a, const vec3& b, float t){return lerp(a,b,t);}

  inline quat Interpolate(const quat& a, const quat& b, float t)
  {
    quat result = mix(a, b, t);
    if (dot(a,b) < 0){
      // neighborhood
      result = mix(a, -b, t);
    }
    return normalized(result);
    // Nlearp, not slerp
  }

  // only quat needs to be normalized, float & vec3 do nothing
  inline float AdjustHermiteResult(float f){return f;}
  inline vec3 AdjustHermiteResult(const vec3& v){return v;}
  inline quat AdjustHermiteResult(const quat& q){return normalized(q);}

  // common Neighborhood op. to make sure quats are in correct Neighborhood
  inline void Neighborhood(const float& a, float& b){}
  inline void Neighborhood(const vec3& a, vec3& b){}
  inline void Neighborhood(const quat& a, quat& b)
  {
    if (dot(a,b) < 0){ b = -b;}
  }
}; // end track helpers

template<typename T, int N>
Track<T, N>::Track()
{
  m_Interpolation = Interpolation::Linear;
}

template<typename T, int N>
float Track<T, N>::GetStartTime()
{
  return m_Frames[0].m_Time;
}

template<typename T, int N>
float Track<T, N>::GetEndTime()
{
  return m_Frames[m_Frames.size() - 1].m_Time;
}

template<typename T, int N>
T Track<T, N>::Sample(float time, bool looping)
{
  // needs to call Constant, Linear or Cubic based on track type
  if(m_Interpolation == Interpolation::Constant)
  {
    return SampleConstant(time, looping);
  }
  else if (m_Interpolation == Interpolation::Linear)
  {
    return SampleLinear(time, looping);
  }
  return SampleCubic(time, looping);
}

template<typename T, int N>
Frame<N>& Track<T, N>::operator[](unsigned int index)
{
  return m_Frames[index];
}

template<typename T, int N>
void Track<T, N>::Resize(unsigned int size)
{
  m_Frames.resize(size);
}

template<typename T, int N>
unsigned int Track<T, N>::Size()
{
  return m_Frames.size();
}

template<typename T, int N>
Interpolation Track<T, N>::GetInterpolation()
{
  return m_Interpolation;
}

template<typename T, int N>
void Track<T, N>::SetInterpolation(Interpolation interp)
{
  m_Interpolation = interp;
}

template<typename T, int N>
T Track<T, N>::Hermite(float t, const T& p1, const T& s1, const T& _p2, const T& s2)
{
  float tt = t * t;
  float ttt = tt * t;
  T p2 = _p2;
  TrackHelpers::Neighborhood(p1, p2);
  float h1 = 2.0f * ttt - 3.0f * tt + 1.0f;
  float h2 = -2.0f * ttt + 3.0f * tt;
  float h3 = ttt - 2.0f * tt + t;
  float h4 = ttt - tt;
  T result = p1 * h1 + p2 *h2 + s1 * h3 + s2 * h4;
  return TrackHelpers::AdjustHermiteResult(result);
}

template<typename T, int N>
int Track<T, N>::FrameIndex(float time, bool looping)
{
  unsigned int size = (unsigned int) m_Frames.size();
  if (size <= 1) {
    return -1;
  }
  if (looping){
    float startTime = m_Frames[0].m_Time;
    float endTime = m_Frames[size - 1].m_Time;
    float duration = endTime - startTime;

    time = fmodf(time - startTime, endTime - startTime);
    if (time < 0.0f)
    {
      time += endTime - startTime;
    }
    time = time + startTime;
  }
  else {
    if (time <= m_Frames[0].m_time)
    {
      return 0;
    }
    if (time >= m_Frames[size -2].m_Time)
    {
      return (int) size -2;
    }
  }

  // time in valid range, loop over m_Frames and return frame that
  // is closest to but less than the time
  for(int i = (int)size -1; i >= 0; --i)
  {
    if (time >= m_Frames[i].m_Time){
      return i;
    }
  }
  // invalid code - shouldn't reach here!
  return -1;
} // end frame index

template<typename T, int N>
float Track<T, N>::AdjustTimeToFitTrack(float time, bool looping)
{
  unsigned int size = (unsigned int) m_Frames.size();
  if (size <= 1){
    return 0.0f;
  }
  float startTime = m_Frames[0].m_Time;
  float endTime = m_Frames[size - 1].m_Time;
  float duration = endTime - startTime;
  if (duration <= 0.0f)
  {
    return 0.0f;
  }
  if (looping){
    time = fmodf(time - startTime, endTime - startTime);
    if(time < 0.0f){
      time += endTime - startTime;
    }
    time = time + startTime;
  }
  else
  {
    if (time <= m_Frames[0].m_Time)
    {
      time = startTime;
    }
    if (time >= m_Frames[size -1].m_Time)
    {
      time = endTime;
    }
  }
  return time;
}

Track<float, 1> t;
float m_AnimTime = 0.0f;
// whenever update called, m_AnimTime is incremented by deltaTime
void Update(float dt)
{
  // todo : actually true?
  m_AnimTime = t.AdjustTimeToFitTrack(m_AnimTime + dt, true);
}

template<> float Track<float, 1>::Cast(float* value)
{
  return value[0];
}

template<> vec3 Track<vec3, 3>::Cast(float* value)
{
  return vec3(value[0], value[1], value[2]);
}

template<> quat Track<quat, 4>::Cast(float* value)
{
  quat r = quat(value[0], value[1], value[2], value[3]);
  return normalized(r);
}

template<typename T, int N>
T Track<T, N>::SampleConstant(float t, bool loop)
{
  int frame = FrameIndex(t, loop);
  if(frame < 0 || frame >= (int) m_Frames.size()){
    return T();
  }
  return Cast(&m_Frames[frame].m_Value[0]);
}

template<typename T, int N>
T Track<T, N>::SampleLinear(float time, bool looping)
{
  int thisFrame = FrameIndex(time, looping);
  if(thisFrame < 0 || thisFrame >= m_Frames.size() - 1)
  {
    return T();
  }
  int nextFrame = thisFrame + 1;
  float trackTime = AdjustTimeToFitTrack(time, looping);
  float thisTime = m_Frames[thisFrame].m_Time;
  float frameDelta = m_Frames[nextFrame].m_Time - thisTime;
  if(frameDelta <= 0.0f)
  {
    return T();
  }
  float t = (trackTime - thisTime) / frameDelta;
  T start = Cast(&m_Frames[thisFrame].m_Value[0]);
  T end   = Cast(&m_Frames[nextFrame].m_Value[0]);
  return TrackHelpers::Interpolate(start, end, t);
}

template<typename T, int N>
T Track<T, N>::SampleCubic(float time, bool looping)
{
  int thisFrame = FrameIndex(time, looping);
  if(thisFrame < 0 || thisFrame >= m_Frames.size() - 1)
  {
    return T();
  }
  int nextFrame = thisFrame + 1;
  float trackTime = AdjustTimeToFitTrack(time, looping);
  float thisTime = m_Frames[thisFrame].m_Time;
  float frameDelta = m_Frames[nextFrame].m_Time - thisTime;
  if(frameDelta <= 0.0f)
  {
    return T();
  }
  float t = (trackTime - thisTime) / frameDelta;
  size_t fltSize = sizeof(float);
  T point1 = Cast(&m_Frames[thisFrame].m_Value[0]);
  T slope1 = m_Frames[thisFrame].m_Out * frameDelta;
  memcpy(&slope1, m_Frames[thisFrame].m_out, N * fltSize);
  slope1 = slope1 * frameDelta;

  T point2 = Cast(&m_Frames[nextFrame].m_Value[0]);
  T slope2 = m_Frames[nextFrame].m_In[0] * frameDelta;
  memcpy(&slope2, m_Frames[nextFrame].m_In, N * fltSize);
  slope2 = slope2 * frameDelta;

  return Hermite(t, point1, slope1, point2, slope2);
}

// TODO Linear Track Sampling location 4426 * page 238/483
