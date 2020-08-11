#pragma once

#include <vector>

template<typename T>
class Attribute
{
public:
  Attribute();
  ~Attribute();

  void SetAttribPointer(unsigned int slot);
  void Set(T* inputArray, unsigned int arrayLength);
  void Set(std::vector<T>& input);
  void BindTo(unsigned int slot);
  void UnBindFrom(unsigned int slot);
  unsigned int Count();
  unsigned int GetHandle();

protected:
  unsigned int m_Handle;
  unsigned int m_Count;

private:
  // attribute data lives on the GPU and don't want multiple
  // handles, so copy constructor disabled
  Attribute(const Attribute& other);
  Attribute& operator=(const Attribute& other);
};
