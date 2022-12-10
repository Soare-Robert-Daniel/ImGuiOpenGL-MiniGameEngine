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

  return modelMatrix;
}
void Transform::ComputeModelMatrix() {
  if (!hasChanged) {
	return;
  }
  auto view = glm::mat4(1.0f);

  view = glm::scale(view, scale);

  view = emath::m_rotate(view, rotation.x, glm::vec3(1.0f, 0, 0));
  view = emath::m_rotate(view, rotation.y, glm::vec3(0, 1.0f, 0));
  view = emath::m_rotate(view, rotation.z, glm::vec3(0, 0, 1.0f));

  view = glm::translate(view, position);

  modelMatrix = view;
}
void Transform::ComputeModelMatrixWithParent(const glm::mat4 &parent) {
  ComputeModelMatrix();
  modelMatrix = parent*modelMatrix;
}
void Transform::SetPosition(const glm::vec3 &newPosition) {
  position = newPosition;
  hasChanged = true;
}
void Transform::SetRotation(const glm::vec3 &newRotation) {
  rotation = newRotation;
  hasChanged = true;
}
void Transform::SetScale(const glm::vec3 &newScale) {
  scale = newScale;
  hasChanged = true;
}

glm::vec3 Transform::getGlobalScale() const {
  return {
	  glm::length(modelMatrix[0]), // RIGHT
	  glm::length(modelMatrix[1]), // UP
	  glm::length(-modelMatrix[2]) // BACKWARD
  };
}
