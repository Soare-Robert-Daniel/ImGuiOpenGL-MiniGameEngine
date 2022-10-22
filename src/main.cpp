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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "CGE by Soare Robert Daniel", nullptr, nullptr);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

    const auto shaderLoader = ShaderLoader::GetInstance();
    shaderLoader->LoadShaderSource(ShaderLoader::VERTEX, vertex_shader_source);
    shaderLoader->LoadShaderSource(ShaderLoader::FRAGMENT, fragment_shader_source);
    const auto shaderProgram = shaderLoader->CreateProgramFromLoadedSources();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    // +---------------- CREATE TRIANGLE ----------------+
    std::vector<CGE::Vertex> vertices = {
            CGE::Vertex{.position = glm::vec3(-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f), .color = glm::vec4(1, 1, 0, 1)}, // Lower left corner
            CGE::Vertex{.position = glm::vec3(0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f), .color = glm::vec4(1, 1, 0, 1)}, // Lower right corner
            CGE::Vertex{.position = glm::vec3(0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f), .color = glm::vec4(1, 1, 0, 1)}, // Upper corner

            CGE::Vertex{.position = glm::vec3(-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f), .color = glm::vec4(1, 1, 0, 1)}, // Inner left
            CGE::Vertex{.position = glm::vec3(0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f), .color = glm::vec4(1, 1, 0, 1)}, // Inner right
            CGE::Vertex{.position = glm::vec3(0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f), .color = glm::vec4(1, 1, 0, 1)}, // Inner down
    };

    // Indices for vertices order
    const std::vector<GLuint> indices =
            {
                    0, 3, 5, // Lower left triangle
                    3, 2, 4, // Lower right triangle
                    5, 4, 1 // Upper triangle
            };

    auto mesh = Mesh("test");
    mesh.AddIndices(indices);
    mesh.AddVertices(vertices);
    mesh.CreateMesh();

    // +---------------- Main Loop ----------------+
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        check_gl_error();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		glUseProgram(shaderProgram);
        mesh.Render();
//		glBindVertexArray(VAO);

//		glDrawArrays(GL_TRIANGLES, 0, 3);

		ImGui::Begin("Custom Game Engine - Soare Robert Daniel");
		ImGui::Text("Test UIS");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);


		glfwPollEvents();

	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);

    shaderLoader->DeleteAllPrograms();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}