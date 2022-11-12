#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// #include <stb/stb_image.h>

#include "emath.h"
#include "ShaderLoader.h"
#include "Mesh.h"
#include "gl_utils.h"
#include <filesystem>
#include "Shader.h"
#include <utility>
#include "Texture.h"
#include "Global.h"
#include "Camera.h"
#include "Model.h"

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
#endif

	GLFWwindow* window = glfwCreateWindow(800, 600, "CGE by Soare Robert Daniel", nullptr, nullptr);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << "WINDOW CREATED." << std::endl;

	gladLoadGL();
	glViewport(0, 0, 800, 800);
    glEnable(GL_DEPTH_TEST);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

    std::cout << "ImGui Init." << std::endl;

    // +---------------- GLOBALS ----------------+
    const auto shaderLoader = ShaderLoader::GetInstance();

    // +---------------- TEXTURE LOADING ----------------+

    std::shared_ptr<Texture> texture(new Texture());
    texture->Load("simple_texture.jpg");
    Global::AddTexture("simple", texture);

    std::cout << "Textures loaded." << std::endl;

    // +---------------- SHADER LOADING ----------------+
    std::shared_ptr<Shader> shader(new Shader());

    shader->AddFile(ShaderLoader::VERTEX, "simple_vertex.glsl");
    shader->AddFile(ShaderLoader::FRAGMENT, "simple_fragment.glsl");
    shader->LoadFiles();

    Global::AddShader("simple", shader);

    std::cout << "Shaders loaded." << std::endl;

    // +---------------- CREATE CUBE ----------------+
    float cube_vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    std::vector<CGE::Vertex> vertices;
    for(int i = 0; i < 180; i += 5) {
        vertices.push_back(
                CGE::Vertex{
                    .position = glm::vec3(cube_vertices[i], cube_vertices[i+1], cube_vertices[i+2]),
                    .color = glm::vec4(1.f, 1.f, 0, 1.f),
                    .normal = glm::vec3(0.0f, 0.0f, 0.0f),
                    .textCoords = glm::vec2(cube_vertices[i+3], cube_vertices[i+4])}
        );
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

    // +---------------- CAMERA SETUP ----------------+
    std::shared_ptr<Camera> camera(new Camera(glm::vec3(-10.0f, 0.0f, 0.0f)));
    camera->SetDistance(10.0f);
    camera->SetTarget(glm::vec3(0));

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    // +---------------- Main Loop ----------------+
	while (!glfwWindowShouldClose(window)) {
        auto currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        HandleInput(window, deltaTime, camera);

        glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        {
            ImGui::Begin("FPS");
            ImGui::Text("%.0f",   glm::round(1.0 / deltaTime));
            ImGui::End();
        }

        ImGui::Render();

        {
            // Resize
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);

            glClearColor(0.30f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            {

                Global::GetShader("simple")->Use();
                Global::GetTexture("simple")->ActivateAndBind(0);

                Global::GetShader("simple")->SetInt("texture0", 0);


                // Global::GetShader("simple")->SetMatrix("model", model);
                {
                    Global::GetShader("simple")->SetMatrix("view", camera->GetView());
                    Global::GetShader("simple")->SetMatrix("projection", projection);
                }


//                Global::GetMesh("square")->Bind();
//
//                glm::vec3 cubePositions[] = {
//                        glm::vec3( 0.0f,  0.0f,  0.0f),
//                        glm::vec3( 2.0f,  5.0f, -15.0f),
//                        glm::vec3(-1.5f, -2.2f, -2.5f),
//                        glm::vec3(-3.8f, -2.0f, -12.3f),
//                        glm::vec3( 2.4f, -0.4f, -3.5f),
//                        glm::vec3(-1.7f,  3.0f, -7.5f),
//                        glm::vec3( 1.3f, -2.0f, -2.5f),
//                        glm::vec3( 1.5f,  2.0f, -2.5f),
//                        glm::vec3( 1.5f,  0.2f, -1.5f),
//                        glm::vec3(-1.3f,  1.0f, -1.5f)
//                };
//                for(unsigned int i = 0; i < 10; i++)
//                {
//                    // calculate the model matrix for each object and pass it to shader before drawing
//                    glm::mat4 model = glm::mat4(1.0f);
//                    model = glm::translate(model, cubePositions[i]);
//                    float angle = 20.0f * (float)i;
//                    if(i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
//                        angle = (float)glfwGetTime() * 25.0f;
//                    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//                    Global::GetShader("simple")->SetMatrix("model", model);
//
//
//                    glDrawArrays(GL_TRIANGLES, 0, 36);
//                }
//
//                Global::GetMesh("square")->Unbind();

                {
                    glm::mat4 model = glm::mat4(1.0f);
                    auto angle = (float)glfwGetTime() * 25.0f;
                    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                    Global::GetShader("simple")->SetMatrix("model", model);
                    model3D->RenderMeshes();

                }

            }

            glUseProgram(0);

            check_gl_error();
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
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ) {
        camera->TranslateForward(deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ) {
        camera->TranslateRight(-deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ) {
        camera->TranslateForward(-deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ) {
        camera->TranslateRight(deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS ) {
        camera->TranslateUpward(-deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS ) {
        camera->TranslateUpward(deltaTime);
    }

    if( glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS ) {
        // Maybe reload the shaders.
    }
}