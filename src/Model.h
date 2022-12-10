//
// Created by Robert on 10.11.2022.
//

#ifndef CGE_MODEL_H
#define CGE_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Mesh.h"
#include "Texture.h"
#include <string>
#include <vector>
#include <utility>

class Model {
 public:
  Model() = default;
  void LoadFromFile(const std::string &filename);
  void NodeImporterHandler(aiNode *node, const aiScene *scene);
  static std::shared_ptr<Mesh> CreateMeshFromNode(aiMesh *mesh);
  void RenderMeshes();

 private:
  std::string name;
  std::vector<std::shared_ptr<Mesh>> meshes;
  std::vector<std::shared_ptr<Texture>> textures;

};

#endif //CGE_MODEL_H
