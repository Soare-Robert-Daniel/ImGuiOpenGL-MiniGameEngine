//
// Created by Robert on 18.10.2022.
//

#ifndef CGE_MESH_H
#define CGE_MESH_H
#include <vector>
#include <string>
#include <glad/glad.h>
#include "Vertex.h"
#include <iostream>


class Mesh {
public:
    Mesh(std::string id) {
        id = std::move(id);
    }

    Mesh* AddIndices( std::vector<GLuint> indices) {
        _indices = indices;
        return this;
    }

    Mesh* AddVertices(std::vector<CGE::Vertex> vertices) {
        _vertices = std::move(vertices);
        return this;
    }

    void CreateMesh() {
        VAO = 0;
        VBO = 0;
        unsigned int IBO = 0;

        // Generate buffer
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO);

        // Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices[0]) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

        // Bind IBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _indices.size(), &_indices[0], GL_STATIC_DRAW);

        // Send the position.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Render() {
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
