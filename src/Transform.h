//
// Created by Robert on 28.11.2022.
//

#ifndef CGE_TRANSFORM_H
#define CGE_TRANSFORM_H

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "emath.h"

class Transform {
 public:
  glm::vec3 position{};
  glm::vec3 rotation{};
  glm::vec3 scale{};

  glm::mat4 modelMatrix = glm::mat4(1.0f);
  bool hasChanged;

  void ComputeModelMatrix();
  void ComputeModelMatrixWithParent(const glm::mat4& parent);

  void SetPosition(const glm::vec3& newPosition);
  void SetRotation(const glm::vec3& newRotation);
  void SetScale(const glm::vec3& newScale);

  glm::vec3 getGlobalScale() const;

  Transform();
  glm::mat4 GetSceneView();
  virtual ~Transform();
};

#endif //CGE_TRANSFORM_H
