//
// Created by Robert on 28.11.2022.
//

#ifndef CGE_TRANSFORM_H
#define CGE_TRANSFORM_H

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "emath.h"

class GameObject;

class Transform {
 public:
  glm::vec3 position{};
  glm::vec3 rotation{};
  glm::vec3 scale{};

  glm::mat4 parent_matrix = glm::mat4(1.0f);
  glm::mat4 model_matrix = glm::mat4(1.0f);
  bool hasChanged{true};

  glm::mat4 GetLocalModelMatrix() const;
  void ComputeModelMatrix();

  void SetPosition(const glm::vec3& new_position);
  void SetRotation(const glm::vec3& new_rotation);
  void SetScale(const glm::vec3& new_scale);

  glm::vec3 GetGlobalLocation(const GameObject* game_object) const;

  glm::vec3 getGlobalScale() const;

  Transform();
  glm::mat4 GetSceneView();
  virtual ~Transform();
};

#endif //CGE_TRANSFORM_H
