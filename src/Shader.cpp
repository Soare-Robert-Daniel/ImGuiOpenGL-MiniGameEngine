//
// Created by Robert on 01.11.2022.
//

#include "Shader.h"
#include "ShaderLoader.h"

int Shader::getId() const {
    return id;
}

void Shader::setId(int id) {
    Shader::id = id;
}

void Shader::Use() const {
    glUseProgram(id);
}

void Shader::AddFile(const ShaderLoader::ShaderType type, const std::string &filepath) {
    this->files.emplace_back(type, filepath);
}

void Shader::Refresh() {
    glDeleteProgram( id );
    LoadFiles();
}

void Shader::LoadFiles() {
    ShaderLoader::singleton_->Clean();
    for(auto& file : files) {
        ShaderLoader::singleton_->LoadShaderFromFile(std::get<0>(file), std::get<1>(file));
    }

    id = ShaderLoader::singleton_->CreateProgramFromLoadedSources();
}

Shader::~Shader() {
    glDeleteProgram( id );
}
