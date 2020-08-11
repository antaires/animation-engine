#include "Attribute.h"
#include "Math.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>

template Attribute<int>;
template Attribute<float>;
template Attribute<vec2>;
template Attribute<vec3>;
template Attribute<vec4>;

template<typename T>
Attribute<T>::Attribute()
{
  glGenBuffers(1, &m_Handle);
  m_Count = 0;
}

template<typename T>
Attribute<T>::~Attribute()
{
  glDeleteBuffers(1, &m_Handle);
}

template<>
void Attribute<int>::SetAttribPointer(unsigned int slot)
{
  glVertexAttribIPointer(slot, 1, GL_INT, 0, (void*) 0);
}
template<>
void Attribute<ivec4>::SetAttribPointer(unsigned int slot)
{
  glVertexAttribIPointer(slot, 4, GL_INT, 0, (void*) 0);
}
template<>
void Attribute<float>::SetAttribPointer(unsigned int slot)
{
  glVertexAttribPointer(slot, 1, GL_FLOAT, GL_FALSE, 0, 0);
}
template<>
void Attribute<vec2>::SetAttribPointer(unsigned int slot)
{
  glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, 0, 0);
}
template<>
void Attribute<vec3>::SetAttribPointer(unsigned int slot)
{
  glVertexAttribPointer(slot, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
template<>
void Attribute<vec4>::SetAttribPointer(unsigned int slot)
{
  glVertexAttribPointer(slot, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

template<typename T>
void Attribute<T>::Set(T* inputArray, unsigned int arrayLength)
{
  m_Count = arrayLength;
  unsigned int size = sizeof(T);
  glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
  glBufferData(GL_ARRAY_BUFFER, size * m_Count, inputArray, GL_STREAM_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void Attribute<T>::Set(std::vector<T>& input)
{
  Set(&input[0], (unsigned int) input.size());
}

template<typename T>
void Attribute<T>::BindTo(unsigned int slot)
{
  glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
  glEnableVertexAttribArray(slot);
  SetAttribPointer(slot);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void Attribute<T>::UnBindFrom(unsigned int slot)
{
  glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
  glDisableVertexAttribArray(slot);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
unsigned int Attribute<T>::Count()
{
  return m_Count;
}

template<typename T>
unsigned int Attribute<T>::GetHandle()
{
  return m_Handle;
}
