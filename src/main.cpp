#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// #include <stb/stb_image.h>
// #include <assimp/aabb.h>

#include "ShaderLoader.h"
#include "Mesh.h"
#include "gl_utils.h"

// Vertex Shader source code
const char* vertex_shader_source = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 color;\n"
"out vec4 vColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   vColor = color;"
"}\0";
//Fragment Shader source code
const char* fragment_shader_source = "#version 330 core\n"
"in vec4 vColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vColor;\n"
"}\n\0";

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "CGE by Soare Robert Daniel", nullptr, nullptr);

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

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

    const auto shaderLoader = ShaderLoader::GetInstance();
    shaderLoader->LoadShaderSource(ShaderLoader::VERTEX, vertex_shader_source);
    shaderLoader->LoadShaderSource(ShaderLoader::FRAGMENT, fragment_shader_source);
    const auto shaderProgram = shaderLoader->CreateProgramFromLoadedSources();

    std::cout << "Shaders loaded." << std::endl;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

    std::cout << "ImGui Init." << std::endl;

    // +---------------- CREATE TRIANGLE ----------------+
    std::vector<CGE::Vertex> vertices = {
            CGE::Vertex{.position = glm::vec3(0.5f, 0.5f, 0.0f), .color = glm::vec4(1.f, 1.f, 0, 1.f)}, // Lower left corner
            CGE::Vertex{.position = glm::vec3(0.5f, -0.5f, 0.0f), .color = glm::vec4(1.f, 0.f, 0, 1.f)}, // Lower right corner
            CGE::Vertex{.position = glm::vec3(-0.5f, -0.5f, 0.0f), .color = glm::vec4(1.f, 0.f, 1.0f, 1.f)}, // Upper corner
            CGE::Vertex{.position = glm::vec3(-0.5f, 0.5f, 0.0f), .color = glm::vec4(1.f, 1.f, 0le, 1.f)}, // Inner left

    };

    // Indices for vertices order
    const std::vector<GLuint> indices =
            {
                   0, 1, 3, // first triangle
                   1, 2, 3  // second triangle
            };

    auto mesh = Mesh("test");
    mesh.AddIndices(indices);
    mesh.AddVertices(vertices);
    mesh.LoadToGPU();

    std::cout << "Mesh Created." << std::endl;

    // +---------------- Main Loop ----------------+
	while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        {
            ImGui::Begin("Custom Game Engine - Soare Robert Daniel");
            ImGui::Text("Test UIS");
            ImGui::End();

        }

        ImGui::Render();

        {
            // Resize
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);

            glClearColor(0.30f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram);
            mesh.Render();
            glUseProgram(0);

            check_gl_error();
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);

	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    shaderLoader->DeleteAllPrograms();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}