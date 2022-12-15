//
// Created by Robert on 28.11.2022.
//

#include "Transform.h"

Transform::Transform() {
  position = glm::vec3(0.0f);
  rotation = glm::vec3(0.0f);
  scale = glm::vec3(1.0f);
}

Transform::~Transform() {

}

glm::mat4 Transform::GetSceneView() {
  if (hasChanged) {
	ComputeModelMatrix();
	hasChanged = false;
  }

  return model_matrix;
}
void Transform::ComputeModelMatrix() {
  if (!hasChanged) {
	return;
  }

  auto scale_matrix = glm::scale(glm::mat4(1.0f), scale);

  auto rot_x_matrix = emath::m_rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0, 0));
  auto rot_y_matrix = emath::m_rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1.0f, 0));
  auto rot_z_matrix = emath::m_rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0, 0, 1.0f));

  model_matrix = glm::translate(glm::mat4(1.0f), position) * ( rot_y_matrix * rot_x_matrix * rot_z_matrix ) * scale_matrix;
}
void Transform::ComputeModelMatrixWithParent(const glm::mat4 &parent) {
  ComputeModelMatrix();
  model_matrix = parent*model_matrix;
}
void Transform::SetPosition(const glm::vec3 &new_position) {
  position = new_position;
  hasChanged = true;
}
void Transform::SetRotation(const glm::vec3 &new_rotation) {
  rotation = new_rotation;
  hasChanged = true;
}
void Transform::SetScale(const glm::vec3 &new_scale) {
  scale = new_scale;
  hasChanged = true;
}

glm::vec3 Transform::getGlobalScale() const {
  return {
	  glm::length(model_matrix[0]), // RIGHT
	  glm::length(model_matrix[1]), // UP
	  glm::length(-model_matrix[2]) // BACKWARD
  };
}
