//
// Created by Robert on 08.11.2022.
//

#ifndef CGE_TEXTURE_H
#define CGE_TEXTURE_H

#include <string>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture {
public:
    Texture() = default;
    void Load(std::string filename);
    void Activate();
    void Bind(unsigned int slot);
    void ActivateAndBind(unsigned int slot);

    virtual ~Texture();

private:
    unsigned int texture;
    int width, height, nrChannels;
};


#endif //CGE_TEXTURE_H
