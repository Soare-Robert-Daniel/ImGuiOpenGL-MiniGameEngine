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
    void RegisterKeyboardInputCallbackTo(GLFWwindow* window);
    void RegisterMouseInputCallbackTo(GLFWwindow* window);
    void SetSpeed(float speed);
    void SetMouseSensitivity(float sens);

    std::shared_ptr<Camera> camera;
    float speed;
    float mouseSensitivity;

    float lastXPos;
    float lastYPos;

    bool lockMouse;

private:
    static void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseCallback(GLFWwindow* window, double xPos, double yPos);

    CameraMovement();
    CameraMovement(CameraMovement const&); // prevent copies
    void operator=(CameraMovement const&); // prevent assignments
};


#endif //CGE_CAMERAMOVEMENT_H