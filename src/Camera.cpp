//
// Created by Robert on 09.11.2022.
//

#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera(const glm::vec3 &pos) : pos(pos) {}

Camera::~Camera() {

}

void Camera::SetTarget(glm::vec3 targetPosition) {
    dir = glm::normalize(pos - targetPosition);
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::normalize(glm::cross(_up, dir));
    up = glm::cross(dir, right);
    view = glm::lookAt( pos, pos - dir, up );
}

void Camera::SetPosition(glm::vec3 position) {
    pos = position;
}

glm::mat4 Camera::GetView() {
    return view;
}
