//
// Created by Robert on 09.11.2022.
//

#ifndef CGE_CAMERA_H
#define CGE_CAMERA_H


#include <glm/glm.hpp>

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
    void RotateFirstPerson_OX(float angle);
    void RotateFirstPerson_OY(float angle);
    void RotateFirstPerson_OZ(float angle);
    void RotateThirdPerson_OX(float angle);
    void RotateThirdPerson_OY(float angle);
    void RotateThirdPerson_OZ(float angle);
    glm::vec3 GetTargetPosition();
    glm::mat4 GetView();

private:
    float dist = 1.0f;
    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::mat4 view;
};


#endif //CGE_CAMERA_H