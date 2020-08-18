#pragma once

class Texture {
  // load texture from file, bind texture index to uniform index
  // and deactivate a texture index
protected:
  unsigned int m_Width;
  unsigned int m_Height;
  unsigned int m_Channels;
  unsigned int m_Handle;
public:
  Texture();
  Texture(const char* path);
  ~Texture();
  void Load(const char* path);
  void Set(unsigned int uniform, unsigned int texIndex);
  void UnSet(unsigned int textureIndex);
  unsigned int GetHandle();
private:
  Texture(const Texture& other);
  Texture& operator=(const Texture& other);
};
