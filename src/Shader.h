//
// Created by Robert on 01.11.2022.
//

#ifndef CGE_SHADER_H
#define CGE_SHADER_H

#include <string>
#include <tuple>
#include <vector>
#include "ShaderLoader.h"

class Shader {
public:
    Shader() = default;

    explicit Shader(int id): id(id) {

    }

private:
    int id{};
    std::string fileName;
    std::vector<std::tuple<ShaderLoader::ShaderType, std::string>> files;

public:
    void Use() const;
    void AddFile(ShaderLoader::ShaderType type, const std::string &filepath );
    void LoadFiles();
    void Refresh();
    int getId() const;

    void setId(int id);

    virtual ~Shader();
};


#endif //CGE_SHADER_H
