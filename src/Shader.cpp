//
// Created by Robert on 01.11.2022.
//

#include "Shader.h"
#include "ShaderLoader.h"

int Shader::getId() const {
    return programId;
}

void Shader::setId(int id) {
    Shader::programId = id;
}

void Shader::Use() const {
    glUseProgram(programId);
}

void Shader::AddFile(const ShaderLoader::ShaderType type, const std::string &filepath) {
    this->files.emplace_back(type, filepath);
}

void Shader::Refresh() {
    glDeleteProgram(programId );
    LoadFiles();
}

void Shader::LoadFiles() {
    ShaderLoader::singleton_->Clean();
    for(auto& file : files) {
        ShaderLoader::singleton_->LoadShaderFromFile(std::get<0>(file), std::get<1>(file));
    }

    programId = ShaderLoader::singleton_->CreateProgramFromLoadedSources();
}

Shader::~Shader() {
    glDeleteProgram(programId );
}

void Shader::SetInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::SetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}

void Shader::SetMatrix(const std::string &name, glm::mat4 matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
