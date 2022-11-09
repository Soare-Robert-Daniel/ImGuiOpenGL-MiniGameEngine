//
// Created by Robert on 09.11.2022.
//

#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera(const glm::vec3 &pos) : pos(pos) {}

Camera::~Camera() {

}

void Camera::SetTarget(glm::vec3 targetPosition) {
    forward = glm::normalize(targetPosition - pos);
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::normalize(glm::cross(forward, _up));
    up = glm::cross(right, forward);
    CalculateView();
}

void Camera::SetPosition(glm::vec3 position) {
    pos = position;
    CalculateView();
}

glm::mat4 Camera::GetView() {
    return view;
}

void Camera::SetDistance(float distance) {
    dist = distance;
    CalculateView();
}

void Camera::CalculateView() {
    view = glm::lookAt(pos, pos + forward, up );
}

void Camera::MoveForward(float distance) {
    glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    pos += dir * distance;
    CalculateView();
}

void Camera::TranslateForward(float distance) {
    glm::vec3 dir = glm::normalize(forward);
    pos += dir * distance;
    CalculateView();
}

void Camera::TranslateUpward(float distance) {
    glm::vec3 dir = glm::normalize(up);
    pos += dir * distance;
    CalculateView();
}

void Camera::TranslateRight(float distance) {
    glm::vec3 dir = glm::normalize(glm::vec3(right.x, 0, right.z));
    pos += dir * distance;
    CalculateView();
}

void Camera::RotateFirstPerson_OX(float angle) {
    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), angle, right);
    forward = glm::vec3( rotMat * glm::vec4(forward, 1));
    forward = glm::normalize(forward);

    up = glm::cross(right, forward);
    CalculateView();
}

void Camera::RotateFirstPerson_OY(float angle) {
    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));
    forward = glm::vec3(rotMat * glm::vec4(forward, 1));
    forward = glm::normalize(forward);

    right = glm::cross(forward, glm::vec3(0, 1, 0));
    up = glm::cross(right, forward);
    CalculateView();
}

void Camera::RotateFirstPerson_OZ(float angle) {
    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), angle, forward);
    right = glm::vec3(rotMat * glm::vec4(right, 1));
    right = glm::normalize(right);

    up = glm::cross(right, forward);
    CalculateView();
}

void Camera::RotateThirdPerson_OX(float angle) {
    TranslateForward(dist);
    RotateFirstPerson_OX(angle);
    TranslateForward(-dist);
}

void Camera::RotateThirdPerson_OY(float angle) {
    TranslateForward(dist);
    RotateFirstPerson_OY(angle);
    TranslateForward(-dist);
}

void Camera::RotateThirdPerson_OZ(float angle) {
    TranslateForward(dist);
    RotateFirstPerson_OZ(angle);
    TranslateForward(-dist);
}

glm::vec3 Camera::GetTargetPosition() {
    return pos + forward * dist;
}
