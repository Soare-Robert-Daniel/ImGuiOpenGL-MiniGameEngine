//
// Created by Robert on 12.11.2022.
//

#ifndef CGE_EMATH_H
#define CGE_EMATH_H
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace emath {
inline glm::vec3 v_add(glm::vec3 a, glm::vec3 b) {
  return a + b;
}

inline glm::vec2 v_add(glm::vec2 a, glm::vec2 b) {
  return a + b;
}

inline glm::vec3 v_mul_scalar(glm::vec3 a, float k) {
  return a*k;
}

inline glm::vec2 v_mul_scalar(glm::vec2 a, float k) {
  return a*k;
}

inline float v_dot(glm::vec3 a, glm::vec3 b) {
  return glm::dot(a, b);
}

inline glm::vec3 v_cross(glm::vec3 a, glm::vec3 b) {
  return glm::cross(a, b);
}

inline float v_dist(glm::vec3 a, glm::vec3 b) {
  return glm::distance(a, b);
}

inline float v_dist(glm::vec2 a, glm::vec2 b) {
  return glm::distance(a, b);
}

inline glm::vec3 v_norm(glm::vec3 a) {
  return glm::normalize(a);
}

inline glm::vec2 v_norm(glm::vec2 a) {
  return glm::normalize(a);
}

inline float v_length(glm::vec3 a) {
  return glm::length(a);
}

inline float v_length(glm::vec2 a) {
  return glm::length(a);
}

inline glm::mat4 m_rotate(glm::mat4 matrix, float angle, glm::vec3 axis) {
  return glm::rotate(matrix, angle, axis);
}

inline glm::mat4 m_lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
  return glm::lookAt(position, target, up);
}
}

#endif //CGE_EMATH_H
