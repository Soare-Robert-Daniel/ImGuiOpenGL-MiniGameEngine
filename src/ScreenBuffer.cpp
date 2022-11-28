//
// Created by Robert on 28.11.2022.
//

#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer() = default;

ScreenBuffer::~ScreenBuffer() {
    Delete();
}

void ScreenBuffer::CreateBuffer() {
    glGenFramebuffers(1, &fbo);
    BindBuffer();
}

void ScreenBuffer::CreateTexture() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ScreenBuffer::CreateRender() {
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
                                                                                                  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
}

void ScreenBuffer::BindBuffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void ScreenBuffer::UnbindBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ScreenBuffer::Create() {
    CreateBuffer();
    CreateTexture();
    CreateRender();

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    UnbindBuffer();
}

void ScreenBuffer::Delete() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &texture);
}
