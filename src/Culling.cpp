//
// Created by Robert on 10.12.2022.
//
#include "Culling.h"

Frustum createFrustumFromCamera(const std::shared_ptr<Camera> camera, float aspect, float fovY, float zNear, float zFar) {

  const float halfVerticalSide = zFar * tanf(fovY * .5f);
  const float halfHorizontalSide = halfVerticalSide * aspect;
  const glm::vec3 frontMultFar = zFar * camera->forward;

  return Frustum{
	  .topFace = { camera->pos, glm::cross(camera->right, frontMultFar - camera->up * halfVerticalSide ) },
	  .bottomFace = { camera->pos, glm::cross( frontMultFar + camera->up * halfVerticalSide, camera->right ) },

	  .rightFace = { camera->pos, glm::cross(camera->up, frontMultFar + camera->right * halfHorizontalSide) },
	  .leftFace = { camera->pos, glm::cross(frontMultFar - camera->right * halfHorizontalSide, camera->up) },

	  .farFace = { camera->pos + frontMultFar * camera->forward, -camera->forward },
	  .nearFace = { camera->pos + zNear * camera->forward, camera->forward },
  };
}

