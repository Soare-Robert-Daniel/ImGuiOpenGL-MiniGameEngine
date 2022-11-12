//
// Created by Robert on 09.11.2022.
//

#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera(const glm::vec3 &pos) : pos(pos) {}

Camera::~Camera() {

}

void Camera::SetTarget(glm::vec3 targetPosition) {
    forward = v_norm(targetPosition - pos);
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = v_norm(v_cross(forward, _up));
    up = v_cross(right, forward);
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
    glm::vec3 dir = v_norm(glm::vec3(forward.x, 0, forward.z));
    pos += dir * distance;

    CalculateView();
}

void Camera::TranslateForward(float distance) {
    glm::vec3 dir = v_norm(forward);
    pos += dir * distance;

    CalculateView();
}

void Camera::TranslateUpward(float distance) {
    glm::vec3 dir = v_norm(up);
    pos += dir * distance;

    CalculateView();
}

void Camera::TranslateRight(float distance) {
    glm::vec3 dir = v_norm(glm::vec3(right.x, 0, right.z));
    pos += dir * distance;

    CalculateView();
}

void Camera::RotateOX_FirstPerson(float angle) {
    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), angle, right);
    forward = v_norm(glm::vec3( rotMat * glm::vec4(forward, 1)));
    up = v_cross(right, forward);

    CalculateView();
}

void Camera::RotateOY_FirstPerson(float angle) {
    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));
    forward = v_norm(glm::vec3(rotMat * glm::vec4(forward, 1)));
    right = v_cross(forward, glm::vec3(0, 1, 0));
    up = v_cross(right, forward);

    CalculateView();
}

void Camera::RotateOZ_FirstPerson(float angle) {
    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), angle, forward);
    right = v_norm(glm::vec3(rotMat * glm::vec4(right, 1)));
    up = v_cross(right, forward);

    CalculateView();
}

void Camera::RotateOX_ThirdPerson(float angle) {
    TranslateForward(dist);
    RotateOX_FirstPerson(angle);
    TranslateForward(-dist);
}

void Camera::RotateOY_ThirdPerson(float angle) {
    TranslateForward(dist);
    RotateOY_FirstPerson(angle);
    TranslateForward(-dist);
}

void Camera::RotateOZ_ThirdPerson(float angle) {
    TranslateForward(dist);
    RotateOZ_FirstPerson(angle);
    TranslateForward(-dist);
}

glm::vec3 Camera::GetTargetPosition() {
    return pos + forward * dist;
}
