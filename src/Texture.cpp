//
// Created by Robert on 08.11.2022.
//

#include "Texture.h"

void Texture::Activate() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::Bind(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
}

void Texture::ActivateAndBind(unsigned int slot) {
    Activate();
    Bind(slot);
}

void Texture::Load(std::string filename) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::cout << "> Start reading the image: " << filename << std::endl;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        std::cout << "|  Loading texture to GPU. Width: " << width << ", Height: " << height  << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "|  Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    std::cout << "|  Texture Loaded" << std::endl;
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}
