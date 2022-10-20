//
// Created by Robert on 18.10.2022.
//

#ifndef CGE_MESH_H
#define CGE_MESH_H
#include <utility>
#include <vector>
#include <string>
#include <glad/glad.h>
#include "Vertex.h"
#include <iostream>


class Mesh {
public:
    explicit Mesh(std::string id) {
        id = std::move(id);
        VBO = -1;
        VAO = -1;
    }

    void AddIndices( std::vector<GLuint> indices) {
        _indices = std::move(indices);
    }

    void AddVertices(std::vector<CGE::Vertex> vertices) {
        _vertices = std::move(vertices);
    }

    void CreateMesh() {
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CGE::Vertex), nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        this->VAO = VAO_;
        this->VBO = VBO_;
    }

    void Render() const {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    virtual ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    std::string id;
    GLuint VAO;
    GLuint VBO;

private:
    std::vector<CGE::Vertex> _vertices;
    std::vector<GLuint> _indices;

};


#endif //CGE_MESH_H
