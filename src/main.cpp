#define STB_IMAGE_IMPLEMENTATION

#include "config.h"
#include "core/camera.h"
#include "core/shader.h"
#include "core/sprite_renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

int main()
{
    // Initialize GLFW.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window.
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD manages function pointers for OpenGL, so initialize GLAD before OpenGL function.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set viewport.
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    uray::Shader* spriteShader = new uray::Shader("../src/shader/sprite.vert.glsl", "../src/shader/sprite.frag.glsl");
    uray::SpriteRenderer* spriteRenderer = new uray::SpriteRenderer("../resource/container.jpg");

    uray::Camera* camera = new uray::Camera();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // Render Loop
    while (!glfwWindowShouldClose(window)) {
        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::vec3 cameraPos = camera->GetPosition();
        cameraPos.x = sin(glfwGetTime()) * 10.0f;
        cameraPos.z = cos(glfwGetTime()) * 10.0f;
        cameraPos.y = 5.0f;
        camera->SetPosition(cameraPos);
        camera->UpdateViewMatrix();

        spriteShader->Use();
        spriteShader->SetMat4("model", model);
        spriteShader->SetMat4("view", camera->GetViewMatrix());
        spriteShader->SetMat4("projection", projection);
        spriteRenderer->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete spriteShader;
    delete spriteRenderer;

    // Clean GLFW's resources.
    glfwTerminate();
    return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}