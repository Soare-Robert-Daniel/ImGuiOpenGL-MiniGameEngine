//
// Created by Robert on 09.11.2022.
//

#ifndef CGE_CAMERA_H
#define CGE_CAMERA_H

#include <glm/glm.hpp>
#include "emath.h"

using namespace emath;

class Camera {
 public:
  explicit Camera(const glm::vec3 &pos);

  virtual ~Camera();

  void SetTarget(glm::vec3 targetPosition);
  void SetPosition(glm::vec3 position);
  void SetDistance(float distance);
  void CalculateView();
  void MoveForward(float distance);
  void TranslateForward(float distance);
  void TranslateUpward(float distance);
  void TranslateRight(float distance);
  void RotateOX_FirstPerson(float angle);
  void RotateOY_FirstPerson(float angle);
  void RotateOZ_FirstPerson(float angle);
  void RotateOX_ThirdPerson(float angle);
  void RotateOY_ThirdPerson(float angle);
  void RotateOZ_ThirdPerson(float angle);
  glm::vec3 GetTargetPosition();
  glm::mat4 GetView();

 private:
  float dist = 1.0f; // distanta de la camera la caracter
  glm::vec3 pos; // pozitia
  glm::vec3 forward; // directia inainte
  glm::vec3 up; // deasupra camerei
  glm::vec3 right; // dreapta camerei
  glm::mat4 view; // matricea cu spatiul camerei
};

#endif //CGE_CAMERA_H
