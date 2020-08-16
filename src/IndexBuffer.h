#pragma once

#include <vector>

class IndexBuffer {
  // index buffers are a type of attribute, used to draw primitives
  // and render a model using indexed geometry
  // to avoid storing multple vertices (overlapping triangles may
  // share the same vertex)
public:
  unsigned int m_Handle;
  unsigned int m_Count;

  IndexBuffer();
  ~IndexBuffer();
  void Set(unsigned int* rr, unsigned int len);
  void Set(std::vector<unsigned int>& input);
  unsigned int Count();
  unsigned int GetHandle();
private:
  // disable copy and assignment to avoid multiple indexbufer objects
  // referencing same OpenGL buffer
  IndexBuffer(const IndexBuffer& other);
  IndexBuffer& operator=(const IndexBuffer& other);
};
