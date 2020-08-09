#pragma once

#include <map>
#include <string>

class Shader
{
private:
  unsigned int m_Handle;
  std::map<std::string, unsigned int> m_Attributes;
  std::map<std::string, unsigned int> m_Uniforms;

public:
  Shader();
  Shader(const std::string& vertex, const std::string& fragment);
  ~Shader();

  void Load(const std::string& vertex, const std::string& fragment);
  void Bind();
  void UnBind();
  unsigned int GetAttribute(const std::string& name);
  unsigned int GetUniform(const std::string& name);
  unsigned int GetHandle();

private:
  std::string ReadFile(const std::string& path);
  unsigned int CompileVertexShader(const std::string& vertex);
  unsigned int CompileFragmentShader(const std::string& fragment);
  bool LinkShaders(unsigned int vertex, unsigned int fragment);
  void PopulateAttributes();
  void PopulateUniforms();


  // disable copy constructor and assignemnt operator
  Shader(const Shader&);
  Shader& operator=(const Shader&);
};
