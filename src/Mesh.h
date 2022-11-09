//
// Created by Robert on 18.10.2022.
//

#ifndef CGE_MESH_H
#define CGE_MESH_H
#include <utility>
#include <vector>
#include <string>
#include "Vertex.h"
#include <glad/glad.h>
#include <iostream>
#include "Shader.h"

class Mesh {
public:
    explicit Mesh(std::string id) {
        id = std::move(id);
        VBO = -1;
        VAO = -1;
    }

    void AddIndices( std::vector<GLuint> indices);

    void AddVertices(std::vector<CGE::Vertex> vertices);

    void LoadToGPU();

    void Render() const;
    void Bind() const;
    static void Unbind() ;

    virtual ~Mesh();

    std::string id;
    GLuint VAO;
    GLuint VBO;

private:
    std::vector<CGE::Vertex> _vertices;
    std::vector<GLuint> _indices;

};


#endif //CGE_MESH_H
