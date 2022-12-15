//
// Created by Robert on 10.12.2022.
//
#include "Culling.h"

Frustum createFrustumFromCamera(const std::shared_ptr<Camera> camera,
								float aspect,
								float fovY,
								float zNear,
								float zFar) {

  const float half_vertical_side = zFar*tanf(fovY*.5f);
  const float half_horizontal_side = half_vertical_side*aspect;
  const glm::vec3 front_mult_far = zFar*camera->forward;

  return Frustum{
	  .topFace = {camera->pos, glm::cross(camera->right, front_mult_far - camera->up*half_vertical_side)},
	  .bottomFace = {camera->pos, glm::cross(front_mult_far + camera->up*half_vertical_side, camera->right)},

	  .rightFace = {camera->pos, glm::cross(camera->up, front_mult_far + camera->right*half_horizontal_side)},
	  .leftFace = {camera->pos, glm::cross(front_mult_far - camera->right*half_horizontal_side, camera->up)},

	  .farFace = {camera->pos + front_mult_far*camera->forward, -camera->forward},
	  .nearFace = {camera->pos + zNear*camera->forward, camera->forward},
  };
}

