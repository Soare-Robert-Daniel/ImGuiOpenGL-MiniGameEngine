#include "CameraMovement.h"

#include <utility>

CameraMovement::CameraMovement() = default;

void CameraMovement::SetCamera(const std::shared_ptr<Camera> &camera) {
  CameraMovement::camera = camera;
}

void CameraMovement::RegisterKeyboardInputCallbackTo(GLFWwindow *window) {
  glfwSetKeyCallback(window, CameraMovement::InputCallback);
}

void CameraMovement::InputCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

//    auto camera = CameraMovement::GetInstance().camera;
//    auto speed = CameraMovement::GetInstance().speed;
//
//    if (key == GLFW_KEY_W && action == GLFW_REPEAT)
//    {
//        camera->TranslateForward(speed);
//    }
//
//    if (key == GLFW_KEY_A && action == GLFW_REPEAT)
//    {
//        camera->TranslateRight(-speed);
//    }
//
//    if (key == GLFW_KEY_S && action == GLFW_REPEAT)
//    {
//        camera->TranslateForward(-speed);
//    }
//
//    if (key == GLFW_KEY_D && action == GLFW_REPEAT)
//    {
//        camera->TranslateRight(speed);
//    }
//
//    if (key == GLFW_KEY_Q && action == GLFW_REPEAT)
//    {
//        camera->TranslateUpward(-speed);
//    }
//
//    if (key == GLFW_KEY_R && action == GLFW_REPEAT)
//    {
//        camera->TranslateUpward(speed);
//    }

  if (mods==GLFW_MOD_CONTROL) {
	CameraMovement::GetInstance().lockMouse = !CameraMovement::GetInstance().lockMouse;
	if (CameraMovement::GetInstance().lockMouse) {
	  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	} else {
	  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
  }
}

CameraMovement &CameraMovement::GetInstance() {
  static CameraMovement instance; // lazy singleton, instantiated on first use
  return instance;
}

void CameraMovement::SetSpeed(const float speed) {
  CameraMovement::speed = speed;
}

void CameraMovement::RegisterMouseInputCallbackTo(GLFWwindow *window) {
  glfwSetCursorPosCallback(window, CameraMovement::MouseCallback);
}

void CameraMovement::MouseCallback(GLFWwindow *window, double xPos, double yPos) {

  if (!CameraMovement::GetInstance().lockMouse) {
	return;
  }

  float offsetX = float(xPos) - CameraMovement::GetInstance().lastXPos;
  float offsetY = float(yPos) - CameraMovement::GetInstance().lastYPos;

  CameraMovement::GetInstance().lastXPos = float(xPos);
  CameraMovement::GetInstance().lastYPos = float(yPos);

  auto camera = CameraMovement::GetInstance().camera;
  auto sens = CameraMovement::GetInstance().mouseSensitivity;

  camera->RotateOX_FirstPerson(sens*offsetY*-1);
  camera->RotateOY_FirstPerson(sens*offsetX*-1);
}

void CameraMovement::SetMouseSensitivity(float sens) {
  mouseSensitivity = sens;
}

void CameraMovement::ProcessInputPerFrame(GLFWwindow *window) const {
  if (glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS) {
	camera->TranslateForward(speed);
  }

  if (glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS) {
	camera->TranslateRight(-speed);
  }

  if (glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS) {
	camera->TranslateForward(-speed);
  }

  if (glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS) {
	camera->TranslateRight(speed);
  }

  if (glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS) {
	camera->TranslateUpward(-speed);
  }

  if (glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS) {
	camera->TranslateUpward(speed);
  }
}
