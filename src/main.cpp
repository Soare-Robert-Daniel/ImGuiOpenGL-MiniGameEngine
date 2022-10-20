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

// Vertex Shader source code
const char* vertex_shader_source = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragment_shader_source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, severity, message );
}

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Vertices coordinates
//	const GLfloat vertices[] =
//	{
//		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
//		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
//		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
//		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
//		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
//		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
//	};


	GLFWwindow* window = glfwCreateWindow(800, 800, "CGE by Soare Robert Daniel", nullptr, nullptr);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback( MessageCallback, nullptr );
	glViewport(0, 0, 800, 800);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

    const auto shaderLoader = ShaderLoader::GetInstance();
    shaderLoader->LoadShaderSource(ShaderLoader::VERTEX, vertex_shader_source);
    shaderLoader->LoadShaderSource(ShaderLoader::FRAGMENT, fragment_shader_source);
    const auto shaderProgram = shaderLoader->CreateProgramFromLoadedSources();

//	GLuint VBO, VAO, EBO;
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_READ);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    std::vector<CGE::Vertex> vertices = {
            CGE::Vertex{ .position = glm::vec3(-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f), .color = glm::vec3(1)}, // Lower left corner
            CGE::Vertex{.position = glm::vec3(0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f), .color =glm::vec3(1)}, // Lower right corner
            CGE::Vertex{.position = glm::vec3(0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f), .color =glm::vec3(1)}, // Upper corner

            CGE::Vertex{.position = glm::vec3(-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f), .color =glm::vec3(1)}, // Inner left
            CGE::Vertex{.position = glm::vec3(0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f), .color =glm::vec3(1)}, // Inner right
            CGE::Vertex{.position = glm::vec3(0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f), .color = glm::vec3(1)}, // Inner down
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


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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