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

    explicit Shader(int id): programId(id) {

    }

private:
    int programId{};
    std::string fileName;
    std::vector<std::tuple<ShaderLoader::ShaderType, std::string>> files;

public:
    void Use() const;

    void SetBool(const std::string& name, bool value);
    void SetFloat(const std::string& name, float value);
    void SetInt(const std::string& name, int value);

    void AddFile(ShaderLoader::ShaderType type, const std::string &filepath );
    void LoadFiles();
    void Refresh();

    int getId() const;
    void setId(int id);

    virtual ~Shader();
};


#endif //CGE_SHADER_H
