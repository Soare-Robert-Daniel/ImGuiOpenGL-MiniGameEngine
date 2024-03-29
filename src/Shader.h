//
// Created by Robert on 01.11.2022.
//

#ifndef CGE_SHADER_H
#define CGE_SHADER_H

#include <string>
#include <tuple>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderLoader.h"
#include "ShaderData.h"

class Shader {
 public:
  Shader() = default;

  explicit Shader(int id) : programId(id) {

  }

 private:
  int programId{};
  std::string fileName;
  std::vector<std::tuple<ShaderLoader::ShaderType, std::string>> files;

 public:
  ShaderData data;

  void Use() const;
  void Stop() const;

  void SetBool(const std::string &name, bool value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetInt(const std::string &name, int value) const;
  void SetVector3(const std::string &name, glm::vec3 vector) const;
  void SetMatrix(const std::string &name, glm::mat4 matrix) const;

  void AddFile(ShaderLoader::ShaderType type, const std::string &filepath);
  void LoadFiles();
  void Refresh();

  int GetId() const;
  void SetId(int id);

  virtual ~Shader();
};

#endif //CGE_SHADER_H
