//
// Created by Robert on 18.10.2022.
//

#include "ShaderLoader.h"
#include <iostream>
#include <stdexcept>

int ShaderLoader::shaderNumber;
ShaderLoader *ShaderLoader::singleton_;

void ShaderLoader::LoadShaderSource(ShaderLoader::ShaderType type, const char *source) {
  GLuint shader;
  switch (type) {
	case VERTEX:shader = glCreateShader(GL_VERTEX_SHADER);
	  break;
	case FRAGMENT:shader = glCreateShader(GL_FRAGMENT_SHADER);
	  break;
	default:throw std::runtime_error("Shader Type not defined.");
  }

  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
	glGetShaderInfoLog(shader, 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  shaderStack.push_back(shader);
}

ShaderLoader::~ShaderLoader() {

}

int ShaderLoader::CreateProgramFromLoadedSources() {
  const auto id = ShaderLoader::shaderNumber;
  ShaderLoader::shaderNumber++;

  const auto program = glCreateProgram();

  for (auto &shader : shaderStack) {
	glAttachShader(program, shader);
  }

  glLinkProgram(program);

  int success;
  char infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
	glGetProgramInfoLog(program, 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::PROGRAM::LINKING\n" << infoLog << std::endl;
  }

  Clean();

  return program;
}

ShaderLoader *ShaderLoader::GetInstance() {
  if (singleton_==nullptr) {
	singleton_ = new ShaderLoader();
  }
  return singleton_;
}

void ShaderLoader::LoadShaderFromFile(ShaderLoader::ShaderType type, const std::string &filepath) {
  std::string fileContent = "";
  std::string readLine = "";

  std::ifstream readFile(filepath.c_str());

  std::cout << "> Read shader file: " << filepath << std::endl;

  if (readFile.is_open()) {
	while (std::getline(readFile, readLine)) {
	  fileContent += readLine + '\n';
	}

	readFile.close();
  } else {
	std::cout << "|  [Shader Loading] " << filepath << " not opened" << std::endl;
  }

  std::cout << "| File read complete." << std::endl;

  this->LoadShaderSource(type, fileContent.c_str());
}

void ShaderLoader::Clean() {
  for (auto &shader : shaderStack) {
	glDeleteShader(shader);
  }

  shaderStack.clear();
}
