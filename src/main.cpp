#define STB_IMAGE_IMPLEMENTATION

#include "config.h"
#include "core/component/camera.h"
#include "core/component/sprite_renderer.h"
#include "core/shader.h"
#include "core/unit.h"

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

    uray::Unit* spriteUnit = new uray::Unit();
    uray::Unit* cameraUnit = new uray::Unit();

    uray::SpriteRenderer* spriteRenderer = new uray::SpriteRenderer("../resource/container.jpg");
    uray::Camera* camera = new uray::Camera();

    cameraUnit->AddComponent(camera);
    spriteUnit->AddComponent(spriteRenderer);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    double lastTime = glfwGetTime();

    // Render Loop
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::vec3 unitPos = spriteUnit->GetPosition();
        unitPos.x += 1.0f * deltaTime;
        spriteUnit->SetPosition(unitPos);

        spriteShader->Use();
        spriteShader->SetMat4("model", spriteUnit->GetModelMatrix());
        spriteShader->SetMat4("view", camera->GetViewMatrix());
        spriteShader->SetMat4("projection", projection);

        cameraUnit->Update();
        spriteUnit->Update();

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