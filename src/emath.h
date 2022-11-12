//
// Created by Robert on 12.11.2022.
//

#ifndef CGE_EMATH_H
#define CGE_EMATH_H
#include <glm/glm.hpp>

namespace emath {
    inline glm::vec3 v_add(glm::vec3 a, glm::vec3 b) {
        return a + b;
    }

    inline glm::vec2 v_add(glm::vec2 a, glm::vec2 b){
        return a + b;
    }

    inline glm::vec3 v_mult(glm::vec3 a, float k) {
        return a * k;
    }

    inline glm::vec2 v_mult(glm::vec2 a, float k) {
        return a * k;
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
}

#endif //CGE_EMATH_H
