//
// Created by Robert on 08.12.2022.
//

#ifndef CGE_SCENERESOURCES_H
#define CGE_SCENERESOURCES_H

#include <memory>s
#include "Camera.h"
#include "Culling.h"

struct SceneResources {
  glm::mat4 projection;
  std::shared_ptr<Camera> camera;
  Frustum frustum;
};

#endif //CGE_SCENERESOURCES_H
