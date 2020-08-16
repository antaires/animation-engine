#include "IndexBuffer.h"
#include "Math.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>

IndexBuffer::IndexBuffer()
{
  glGenBuffers(1, &m_Handle);
  m_Count = 0;
}

IndexBuffer::~IndexBuffer()
{
  glDeleteBuffers(1, &m_Handle);
}

void IndexBuffer::Set(unsigned int* inputArr, unsigned int arrLen)
{
  m_Count = arrLen;
  unsigned int size = sizeof(unsigned int);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * m_Count, inputArr, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Set(std::vector<unsigned int>& input)
{
  Set(&input[0], (unsigned int) input.size());
}

unsigned int IndexBuffer::Count()
{ return m_Count; }

unsigned int IndexBuffer::GetHandle()
{ return m_Handle; }
