//
// Created by Robert on 02.11.2022.
//

#ifndef CGE_GLOBAL_H
#define CGE_GLOBAL_H

#include <unordered_map>
#include <utility>
#include <string_view>
#include <string>
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

class Global {

 public:
  static std::shared_ptr<Shader> GetShader(const std::string &name) {
	return shaders[name];
  }

  static void AddShader(const std::string &name, std::shared_ptr<Shader> shader) {
	shaders[name] = std::move(shader);
  }

  static std::shared_ptr<Mesh> GetMesh(const std::string &name) {
	return meshes[name];
  }

  static void AddMesh(const std::string &name, std::shared_ptr<Mesh> mesh) {
	meshes[name] = std::move(mesh);
  }

  static std::shared_ptr<Texture> GetTexture(const std::string &name) {
	return textures[name];
  }

  static void AddTexture(const std::string &name, std::shared_ptr<Texture> texture) {
	textures[name] = std::move(texture);
  }

 private:
  inline static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
  inline static std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
  inline static std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
};

#endif //CGE_GLOBAL_H
