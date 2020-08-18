#include "Texture.h"
#include "stb_image.h"
#include <GL/glew.h>


Texture::Texture()
{
  m_Width = 0; m_Height = 0; m_Channels = 0;
  glGenTextures(1, &m_Handle);
}

Texture::Texture(const char* path)
{
    glGenTextures(1, &m_Handle);
    Load(path);
}

Texture::~Texture()
{
  glDeleteTextures(1, &m_Handle);
}

void Texture::Load(const char* path)
{
// all textures loaded with RGBA channels
  glBindTexture(GL_TEXTURE_2D, m_Handle);
  int width, height, channels;
  unsigned char* data = stbi_load(path, &width, &height, &channels, 4);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  m_Width = width;
  m_Height = height;
  m_Channels = channels;
}

void Texture::Set(unsigned int uniformIndex, unsigned int textureIndex)
{
  glActiveTexture(GL_TEXTURE0 + textureIndex);
  glBindTexture(GL_TEXTURE_2D, m_Handle);
  glUniform1i(uniformIndex, textureIndex);
}

void Texture::UnSet(unsigned int textureIndex)
{
  glActiveTexture(GL_TEXTURE0 + textureIndex);
  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);
}

unsigned int Texture::GetHandle()
{
  return m_Handle;
}
