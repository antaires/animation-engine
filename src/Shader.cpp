#include "Shader.h"

// public
Shader::Shader(){}
Shader::Shader(const std::string& vertex, const std::string& fragment){}
Shader::~Shader(){}

void Shader::Load(const std::string& vertex, const std::string& fragment){}
void Shader::Bind(){}
void Shader::UnBind(){}
unsigned int Shader::GetAttribute(const std::string& name){return 0;}
unsigned int Shader::GetUniform(const std::string& name){return 0;}
unsigned int Shader::GetHandle(){return 0;}

// private
std::string Shader::ReadFile(const std::string& path){return "";}
unsigned int Shader::CompileVertexShader(const std::string& vertex) {return 0;}
unsigned int Shader::CompileFragmentShader(const std::string& fragment) {return 0;}
bool Shader::LinkShaders(unsigned int vertex, unsigned int fragment) {return false;}
void Shader::PopulateAttributes() {}
void Shader::PopulateUniforms() {}
