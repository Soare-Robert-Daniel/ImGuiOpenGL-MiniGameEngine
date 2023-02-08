#include <memory>
#include <filesystem>
#include <iostream>
#include <vector>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ShaderLoader.h"
#include "Mesh.h"
#include "gl_utils.h"
#include "Shader.h"
#include "Texture.h"
#include "Global.h"
#include "Model.h"
#include "emath.h"
#include "Camera.h"
#include "CameraMovement.h"
#include "ScreenBuffer.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Culling.h"
#include "Lighting.h"
#include "ContinuousRotationComponent.h"
#include "SceneParser.h"

const float movementSpeed = 2.0f;

void HandleInput(GLFWwindow *window, float deltaTime, std::shared_ptr<Camera> camera);

int main() {
  auto p = std::filesystem::current_path();
  std::cout << p << std::endl;

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RED_BITS, 8);
  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_ALPHA_BITS, 8);
  glfwWindowHint(GLFW_DEPTH_BITS, 32);
#endif

  GLFWwindow *window = glfwCreateWindow(800, 600, "CGE by Soare Robert Daniel", nullptr, nullptr);

  if (window==nullptr) {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	std::cout << "Failed to initialize GLAD" << std::endl;
	return -1;
  }

  std::cout << "WINDOW CREATED." << std::endl;

  gladLoadGL();
  glViewport(0, 0, 800, 800);
  glEnable(GL_DEPTH_TEST);

  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

  glfwSwapBuffers(window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330 core");

  std::cout << "ImGui Init." << std::endl;

  // +---------------- GLOBALS ----------------+
  const auto shaderLoader = ShaderLoader::GetInstance();

  // +---------------- TEXTURE LOADING ----------------+

  std::shared_ptr<Texture> texture(new Texture());
  texture->Load("simple_texture.jpg");
  Global::AddTexture("simple", texture);

  std::shared_ptr<Texture> texture1(new Texture());
  texture1->Load("second_simple.jpg");
  Global::AddTexture("second_simple", texture1);

  std::shared_ptr<Texture> texture2(new Texture());
  texture2->Load("Gravel_001_BaseColor.jpg");
  Global::AddTexture("Gravel_001_BaseColor", texture2);

  std::shared_ptr<Texture> texture3(new Texture());
  texture3->Load("Gravel_001_Normal.jpg");
  Global::AddTexture("Gravel_001_Normal", texture3);

  std::cout << "Textures loaded." << std::endl;

  // +---------------- SHADER LOADING ----------------+
  std::shared_ptr<Shader> shader(new Shader());
  shader->data = {.texture_num = 1, .normal_num = 0};
  shader->AddFile(ShaderLoader::VERTEX, "simple_vertex.glsl");
  shader->AddFile(ShaderLoader::FRAGMENT, "simple_fragment.glsl");
  shader->LoadFiles();

  Global::AddShader("simple", shader);

  std::shared_ptr<Shader> shader1(new Shader());
  shader1->data = {.texture_num = 1, .normal_num = 1};
  shader1->AddFile(ShaderLoader::VERTEX, "normal_vertex.glsl");
  shader1->AddFile(ShaderLoader::FRAGMENT, "normal_fragment.glsl");
  shader1->LoadFiles();

  Global::AddShader("normal", shader1);

  std::cout << "Shaders loaded." << std::endl;

  // +---------------- CREATE CUBE ----------------+
  float cube_vertices[] = {
	  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	  0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	  0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	  0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	  -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	  0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	  -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

	  -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	  -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	  -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	  0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	  0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	  0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	  0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	  0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	  0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	  0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	  -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	  0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	  -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	  -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

  std::vector<CGE::Vertex> vertices;
  for (int i = 0; i < 180; i += 5) {
	vertices.push_back(
		CGE::Vertex{
			.position = glm::vec3(cube_vertices[i], cube_vertices[i + 1], cube_vertices[i + 2]),
			.color = glm::vec4(1.f, 1.f, 0, 1.f),
			.normal = glm::vec3(0.0f, 0.0f, 0.0f),
			.textCoords = glm::vec2(cube_vertices[i + 3], cube_vertices[i + 4])});
  }

  // Indices for vertices order
  const std::vector<GLuint> indices =
	  {
		  0, 1, 3, // first triangle
		  1, 2, 3  // second triangle
	  };

  std::shared_ptr<Mesh> mesh(new Mesh("test"));
  mesh->AddIndices(indices);
  mesh->AddVertices(vertices);
  mesh->LoadToGPU();

  Global::AddMesh("square", mesh);

  std::cout << "Mesh Created." << std::endl;

  // +---------------- IMPORT MODEL ----------------+
  std::shared_ptr<Model> model3D(new Model());
  model3D->LoadFromFile("test_model.obj");
  Global::AddModel("simple", model3D);

  std::shared_ptr<Model> model3D1(new Model());
  model3D1->LoadFromFile("cube_test.obj");
  Global::AddModel("cube", model3D1);

  // +---------------- CAMERA SETUP ----------------+
  std::shared_ptr<Camera> camera(new Camera(glm::vec3(-10.0f, 3.0f, 3.0f)));
  camera->SetDistance(10.0f);
  camera->SetTarget(glm::vec3(0));

  CameraMovement &cameraMovement = CameraMovement::GetInstance();
  cameraMovement.SetMouseSensitivity(0.0001f);
  cameraMovement.SetCamera(camera);
  cameraMovement.RegisterKeyboardInputCallbackTo(window);
  CameraMovement::RegisterMouseInputCallbackTo(window);

  float delta_time = 0.0f; // Time between current frame and last frame
  float last_frame = 0.0f; // Time of last frame

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
  camera->frustumData = {
	  .aspect = 800.0f/600.0f,
	  .fovY = glm::radians(45.0f),
	  .zNear = 0.01f,
	  .zFar = 100.0f
  };


  // Screen Frame Buffer
  std::unique_ptr<ScreenBuffer> screen_buffer(new ScreenBuffer());
  screen_buffer->width = 800;
  screen_buffer->height = 800;
  screen_buffer->Create();

  // Scene Root

  std::shared_ptr<GameObject> sceneRoot(new GameObject());

  // Lighting
  // LightingData lighting_data = {.position = camera->pos, .color = glm::vec3(0.3f, 0.5f, 0.0f)};

  SceneResources scene_resources = {.projection = projection, .camera = camera }; //}, .lighting_data = lighting_data};

  SceneParser::ParseConfigFile("scene.json", scene_resources, sceneRoot);

  sceneRoot->Start();

  int renderedObjects = 0;
  // +---------------- Main Loop ----------------+
  while (!glfwWindowShouldClose(window)) {

	renderedObjects = 0;
	auto currentFrame = (float)glfwGetTime();
	delta_time = currentFrame - last_frame;
	last_frame = currentFrame;
	scene_resources.delta_time = delta_time;

	cameraMovement.SetSpeed(delta_time*10.0f);
	cameraMovement.ProcessInputPerFrame(window);

	scene_resources.frustum = createFrustumFromCamera(
		camera,
		camera->frustumData.aspect,
		camera->frustumData.fovY,
		camera->frustumData.zNear,
		camera->frustumData.zFar
	);

	// HandleInput(window, delta_time, camera);
	screen_buffer->BindBuffer();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	{

	  glClearColor(0.30f, 0.13f, 0.17f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  {
		sceneRoot->Update(scene_resources);
	  }

	  glUseProgram(0);

	  check_gl_error();
	  screen_buffer->UnbindBuffer();
	  glClearColor(0.0f, 0.13f, 0.0f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	{
	  ImGui::NewFrame();

	  {
		ImGui::Begin("Scene");
		ImGui::Text("Camera Pos: %.0f %.0f %.0f", camera->pos.x, camera->pos.y, camera->pos.z);
		ImGui::Text("FPS: %.0f", glm::round(1.0/delta_time));
		ImGui::Text("Cursor Lock: %s", CameraMovement::GetInstance().lockMouse ? "ON" : "OFF");
		ImGui::Text("Rendered Objs: %d", sceneRoot->CountRenderedObjects());
		if( ImGui::Button("Lock Mouse")) {
		  CameraMovement::GetInstance().lockMouse = true;
		  if (CameraMovement::GetInstance().lockMouse) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		  } else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		  }
		}
		ImGui::End();
	  }

	  {
		ImGui::Begin("Game");
		{
		  ImGui::BeginChild("Render");
		  // Get the size of the child (i.e. the whole draw size of the windows).
		  ImVec2 wsize = ImGui::GetWindowSize();
		  // Because I use the texture from OpenGL, I need to invert the V from the UV.
		  ImGui::Image((ImTextureID)(intptr_t)screen_buffer->texture, wsize, ImVec2(0, 1), ImVec2(1, 0));
		  ImGui::EndChild();

		  if (screen_buffer->NeedToResize(wsize.x, wsize.y)) {
			screen_buffer->Resize(wsize.x, wsize.y);
			glViewport(0, 0, wsize.x, wsize.y);
		  }
		}
		ImGui::End();
	  }
	  ImGui::ShowMetricsWindow();

	  ImGui::Render();
	}

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
	glfwPollEvents();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void HandleInput(GLFWwindow *window, float deltaTime, std::shared_ptr<Camera> camera) {
  if (glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS) {
	camera->TranslateForward(deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS) {
	camera->TranslateRight(-deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS) {
	camera->TranslateForward(-deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS) {
	camera->TranslateRight(deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS) {
	camera->TranslateUpward(-deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS) {
	camera->TranslateUpward(deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_R)==GLFW_PRESS) {
	// Maybe reload the shaders.
  }
}