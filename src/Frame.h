#pragma once

template<unsigned int N>
class Frame {
public:
  // stores keyframes in an animation track
  float m_Value[N];
  float m_In[N];
  float m_Out[N];
  float m_Time;

  typedef Frame<1>
  ScalarFrame;
  
  typedef Frame<3>
  VectorFrame;

  typedef Frame<4>
  QuaternionFrame;
};
