//
// Created by Robert on 28.11.2022.
//

#ifndef CGE_TRANSFORMCOMPONENT_H
#define CGE_TRANSFORMCOMPONENT_H


#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "emath.h"

class TransformComponent {
public:
    glm::vec3 position{};
    glm::vec3 rotation{};
    glm::vec3 scale{};

    TransformComponent();
    glm::mat4 GetSceneView() const;
    virtual ~TransformComponent();
};


#endif //CGE_TRANSFORMCOMPONENT_H
