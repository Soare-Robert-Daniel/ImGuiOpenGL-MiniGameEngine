//
// Created by Robert on 28.11.2022.
//

#include "TransformComponent.h"

TransformComponent::TransformComponent() {
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
}

TransformComponent::~TransformComponent() {

}

glm::mat4 TransformComponent::GetSceneView() const {
    auto view = glm::mat4(1.0f);

    view = glm::scale(view, scale);

    view = emath::m_rotate(view, rotation.x, glm::vec3(1.0f, 0, 0) );
    view = emath::m_rotate(view, rotation.y, glm::vec3(0, 1.0f, 0) );
    view = emath::m_rotate(view, rotation.z, glm::vec3(0, 0, 1.0f) );

    view = glm::translate(view, position);

    return view;
}
