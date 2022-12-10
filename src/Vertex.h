//
// Created by Robert on 18.10.2022.
//

#pragma once
#include <glm/glm.hpp>

namespace CGE {

struct Vertex {
  glm::vec3 position;
  glm::vec4 color;
  glm::vec3 normal;
  glm::vec2 textCoords;
};

} // CGE


