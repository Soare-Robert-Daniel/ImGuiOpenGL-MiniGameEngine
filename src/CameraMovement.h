#ifndef CGE_CAMERAMOVEMENT_H
#define CGE_CAMERAMOVEMENT_H

#include <utility>
#include "Camera.h"

class CameraMovement {
public:
    CameraMovement();
    void SetCamera(std::shared_ptr<Camera> camera);
    void RegisterInputCallbackTo(GLFWwindow* window);

private:
    void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    std::shared_ptr<Camera> camera;    
};


#endif //CGE_CAMERAMOVEMENT_H