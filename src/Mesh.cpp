//
// Created by Robert on 18.10.2022.
//

// #include "gl_utils.h"
#include "Mesh.h"
#include <iostream>

void Mesh::AddIndices(std::vector<GLuint> indices) {
    _indices = std::move(indices);
}

void Mesh::AddVertices(std::vector<CGE::Vertex> vertices) {
    _vertices = std::move(vertices);
}

void Mesh::LoadToGPU() {
    GLuint VAO_ = 0;
    GLuint VBO_ = 0;
    GLuint IBO_ = 0;

    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    // Bind VBO
    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices[0]) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

    // Bind IBO
    glGenBuffers(1, &IBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _indices.size(), &_indices[0], GL_STATIC_DRAW);

    // Send the position.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CGE::Vertex), (void*)0);

    // Send the color.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CGE::Vertex), (void*)(sizeof(glm::vec3)));

    // Send the normal.
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(CGE::Vertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4)));

    // Send the text coordinates.
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(CGE::Vertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec3)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->VAO = VAO_;
    this->VBO = VBO_;
}

void Mesh::Render() const {
    Bind();
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    Unbind();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::Bind() const {
    glBindVertexArray(VAO);
}

void Mesh::Unbind() {
    glBindVertexArray(0);
}
