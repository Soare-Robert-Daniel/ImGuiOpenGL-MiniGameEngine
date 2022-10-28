//
// Created by Robert on 18.10.2022.
//

#include "ShaderLoader.h"
#include <iostream>

int ShaderLoader::shaderNumber;
ShaderLoader* ShaderLoader::singleton_;

void ShaderLoader::LoadShaderSource(ShaderLoader::ShaderType type, const char *source) {
    GLuint shader;
    switch (type) {
        case VERTEX:
            shader = glCreateShader(GL_VERTEX_SHADER);
            break;
        case FRAGMENT:
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderStack.push_back(shader);
}

ShaderLoader::~ShaderLoader() {
    DeleteAllPrograms();
}

int ShaderLoader::CreateProgramFromLoadedSources() {
    const auto id = ShaderLoader::shaderNumber;
    ShaderLoader::shaderNumber++;

    const auto program = glCreateProgram();

    for( auto& shader : shaderStack ) {
        glAttachShader(program, shader);
    }

    glLinkProgram( program );

    int  success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING\n" << infoLog << std::endl;
    }


    shaderPrograms.insert(std::pair<int, GLuint>(id, program));

    for( auto& shader : shaderStack ) {
        glDeleteShader(shader);
    }

    shaderStack.clear();

    return program;
}

void ShaderLoader::DeleteAllPrograms() {
    for( auto& program : shaderPrograms) {
        glDeleteProgram( program.second );
    }

    shaderPrograms.clear();
}

ShaderLoader *ShaderLoader::GetInstance() {
    if(singleton_==nullptr){
        singleton_ = new ShaderLoader();
    }
    return singleton_;
}
