#ifndef CGE_CAMERAMOVEMENT_H
#define CGE_CAMERAMOVEMENT_H

#include <utility>
#include "Camera.h"
#include <memory>
#include <GLFW/glfw3.h>
#include <iostream>

class CameraMovement {
public:

    static CameraMovement& GetInstance();
    void SetCamera(const std::shared_ptr<Camera>& camera);
    void RegisterInputCallbackTo(GLFWwindow* window);
    void SetSpeed(float speed);

private:
    static void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    std::shared_ptr<Camera> camera;
    float speed;

    CameraMovement();
    CameraMovement(CameraMovement const&); // prevent copies
    void operator=(CameraMovement const&); // prevent assignments
};


#endif //CGE_CAMERAMOVEMENT_H