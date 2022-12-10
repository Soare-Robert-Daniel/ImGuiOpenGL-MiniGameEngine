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

  Transform();
  glm::mat4 GetSceneView() const;
  virtual ~Transform();
};

#endif //CGE_TRANSFORM_H
