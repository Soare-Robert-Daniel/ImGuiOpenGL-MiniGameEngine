//
// Created by Robert on 12.11.2022.
//

#ifndef CGE_EMATH_H
#define CGE_EMATH_H
#include <glm/glm.hpp>

using namespace glm;

namespace emath {
    vec3 v_add(vec3 a, vec3 b) {
        return a + b;
    }

    vec2 v_add(vec2 a, vec2 b){
        return a + b;
    }

    vec3 v_mult(vec3 a, float k) {
        return a * k;
    }

    vec2 v_mult(vec2 a, float k) {
        return a * k;
    }

    float v_dot(vec3 a, vec3 b) {
        return dot(a, b);
    }

    vec3 v_cross(vec3 a, vec3 b) {
        return cross(a, b);
    }

    float v_dist(vec3 a, vec3 b) {
        return distance(a, b);
    }

    float v_dist(vec2 a, vec2 b) {
        return distance(a, b);
    }

    vec3 v_norm(vec3 a) {
        return normalize(a);
    }

    vec2 v_norm(vec2 a) {
        return normalize(a);
    }

    float v_length(vec3 a) {
        return length(a);
    }

    float v_length(vec2 a) {
        return length(a);
    }
}

#endif //CGE_EMATH_H
