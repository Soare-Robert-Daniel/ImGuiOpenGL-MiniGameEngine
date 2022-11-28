//
// Created by Robert on 28.11.2022.
//

#ifndef CGE_SCREENBUFFER_H
#define CGE_SCREENBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class ScreenBuffer {
public:
    unsigned int fbo;
    unsigned int texture;
    unsigned int rbo;

    int width;
    int height;

    void Create();
    void CreateBuffer();
    void CreateTexture();
    void CreateRender();
    void BindBuffer() const;
    bool NeedToResize(int w, int h);
    void Resize(int w, int h);
    static void UnbindBuffer();

    void Delete();

    ScreenBuffer();
    virtual ~ScreenBuffer();
};


#endif //CGE_SCREENBUFFER_H
