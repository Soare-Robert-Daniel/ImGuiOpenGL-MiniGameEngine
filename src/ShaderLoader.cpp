//
// Created by Robert on 18.10.2022.
//

#include "ShaderLoader.h"

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
    shaderPrograms.insert(std::pair<int, GLuint>(id, program));

    for( auto& shader : shaderStack ) {
        glDeleteShader(shader);
    }

    shaderStack.clear();

    return id;
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
