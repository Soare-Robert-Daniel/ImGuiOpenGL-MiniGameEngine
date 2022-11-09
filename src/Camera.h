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
    glm::mat4 GetView();

private:
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 up;
    glm::vec3 right;
    glm::mat4 view;
};


#endif //CGE_CAMERA_H
