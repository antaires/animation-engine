#pragma once

#include "Interpolation.h"
#include "Frame.h"
#include "Math.h"
#include <vector>

template<typename T, int N>
class Track {
  // a track is a collection of frames
protected:
  std::vector<Frame<N>> m_Frames;
  Interpolation m_Interpolation;

public:
  Track();
  void Resize(unsigned int size);
  unsigned int Size();
  Interpolation GetInterpolation();
  void SetInterpolation(Interpolation interp);
  float GetStartTime();
  float GetEndTime();
  T Sample(float time, bool looping);
  Frame<N>& operator[](unsigned int index);

  float AdjustTimeToFitTrack(float t, bool loop);

protected:
  // helpers
  T SampleConstant(float time, bool looping);
  T SampleLinear(float time, bool looping);
  T SampleCubic(float time, bool looping);
  // hermite splites
  T Hermite(float time, const T& p1, const T& s1, const T& p2, const T& s2);
  // get frame index for give time = last frame rigth before requested time
  int FrameIndex(float time, bool looping);
  T Cast(float* value); // will be specialized

  typedef Track<float, 1>
  ScalarTrack;
  typedef Track<float,3>
  VectorTrack;
  typedef Track<float, 4>
  QuaternionTrack;
};
