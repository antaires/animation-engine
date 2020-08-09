#include "Shader.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>

// public
Shader::Shader()
{
    m_Handle = glCreateProgram();
}

Shader::Shader(const std::string& vertex, const std::string& fragment)
{
    m_Handle = glCreateProgram();
    Load(vertex, fragment);
}

Shader::~Shader()
{
  glDeleteProgram(m_Handle);
}

void Shader::Load(const std::string& vertex, const std::string& fragment)
{
  std::ifstream f(vertex.c_str());
  bool vertFile = f.good();
  f.close();
  f = std::ifstream(vertex.c_str());
  bool fragFile = f.good();
  f.close();
  std::string v_source = vertex;
  if (vertFile)
  {
    v_source = ReadFile(vertex);
  }
  std::string f_source = fragment;
  if (fragFile)
  {
    f_source = ReadFile(fragment);
  }
  unsigned int vert = CompileVertexShader(v_source);
  unsigned int frag = CompileFragmentShader(f_source);
  if(LinkShaders(vert, frag))
  {
    PopulateAttributes();
    PopulateUniforms();
  }
}

void Shader::Bind()
{
  glUseProgram(m_Handle);
}

void Shader::UnBind()
{
  glUseProgram(0);
}

unsigned int Shader::GetAttribute(const std::string& name)
{
  // if given attrib name present, integer representing it is returned
  // if not, 0 returned
  std::map<std::string, unsigned int>::iterator it =
    m_Attributes.find(name);
  if(it == m_Attributes.end())
  {
    std::cout<<"Bad attrib index: "<< name << "\n";
    return 0;
  }
  return it->second;
}

unsigned int Shader::GetUniform(const std::string& name)
{
  std::map<std::string, unsigned int>::iterator it =
    m_Uniforms.find(name);
  if(it == m_Uniforms.end())
  {
    std::cout<<"Bad uniform index: "<< name << "\n";
    return 0;
  }
  return it->second;
}

unsigned int Shader::GetHandle()
{
  return m_Handle;
}

// private
std::string Shader::ReadFile(const std::string& path)
{
  std::ifstream file;
  file.open(path);
  std::stringstream contents;
  contents << file.rdbuf();
  file.close();
  return contents.str();
}

unsigned int Shader::CompileVertexShader(const std::string& vertex)
{
    unsigned int v = glCreateShader(GL_VERTEX_SHADER);
    const char* v_source = vertex.c_str();
    glShaderSource(v, 1, &v_source, NULL);
    glCompileShader(v);
    int success = 0;
    glGetShaderiv(v, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      char infoLog[512];
      glGetShaderInfoLog(v, 512, NULL, infoLog);
      std::cout<<"Vertex compilation failed\n";
      std::cout<<"\t"<<infoLog<<"\n";
      glDeleteShader(v);
      return 0;
    }
    return v;
}

unsigned int Shader::CompileFragmentShader(const std::string& fragment)
{
  unsigned int f = glCreateShader(GL_FRAGMENT_SHADER);
  const char* f_source = fragment.c_str();
  glShaderSource(f, 1, &f_source, NULL);
  glCompileShader(f);
  int success = 0;
  glGetShaderiv(f, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(f, 512, NULL, infoLog);
    std::cout<<"Fragment compilation failed\n";
    std::cout<<"\t"<<infoLog<<"\n";
    glDeleteShader(f);
    return 0;
  }
  return f;
}

bool Shader::LinkShaders(unsigned int vertex, unsigned int fragment)
{
  glAttachShader(m_Handle, vertex);
  glAttachShader(m_Handle, fragment);
  glLinkProgram(m_Handle);
  int success = 0;
  glGetProgramiv(m_Handle, GL_LINK_STATUS, &success);
  if(!success)
  {
    char infoLog[512];
    glGetProgramInfoLog(m_Handle, 512, NULL, infoLog);
    std::cout<<"ERROR: Shader linking failed\n";
    std::cout<<"\t"<<infoLog<<"\n";
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return false;
  }
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  return true;
}

void Shader::PopulateAttributes()
{
  int count = -1;
  int length;
  char name[128];
  int size;
  GLenum type;
  glUseProgram(m_Handle);
  glGetProgramiv(m_Handle, GL_ACTIVE_ATTRIBUTES, &count);
  for(int i = 0; i < count; ++i)
  {
    memset(name, 0, sizeof(char) * 128);
    glGetActiveAttrib(m_Handle, (GLuint)i, 128, &length, &size, &type, name);
    int attrib = glGetAttribLocation(m_Handle, name);
    if (attrib >= 0)
    {
      m_Attributes[name] = attrib;
    }
  }
  glUseProgram(0);
}

void Shader::PopulateUniforms()
{
  int count = -1;
  int length;
  char name[128];
  int size;
  GLenum type;
  char testName[256];
  glUseProgram(m_Handle);
  glGetProgramiv(m_Handle, GL_ACTIVE_UNIFORMS, &count);
  for(int i = 0; i < count; ++i)
  {
    memset(name, 0, sizeof(char) * 128);
    glGetActiveUniform(m_Handle, (GLuint)i, 128, &length, &size, &type, name);
    int uniform = glGetUniformLocation(m_Handle, name);
    if (uniform >= 0)
    {
      // is uniform valid?
      // search for array bracket in name to see if its an array
      std::string uniformName = name;
      std::size_t found = uniformName.find('[');
      if(found != std::string::npos)
      {
        // uniform array
        uniformName.erase(uniformName.begin() + found, uniformName.end());
        unsigned int uniformIndex = 0;
        while(true)
        {
          memset(testName, 0, sizeof(char)*256);
          std::sprintf(testName, "%s[%d]", uniformName.c_str(), uniformIndex++);
          int uniformLocation = glGetUniformLocation(m_Handle, testName);
          if(uniformLocation < 0){
            break;
          }
          m_Uniforms[testName] = uniformIndex;
          m_Uniforms[uniformName] = uniform;
        }
      }
      glUseProgram(0);
    }
  }
}
