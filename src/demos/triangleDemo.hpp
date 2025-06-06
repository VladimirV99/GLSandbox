#ifndef TRIANGLEDEMO_H
#define TRIANGLEDEMO_H

#include <imgui.h>

#include "demo.hpp"
#include "shader.hpp"

class TriangleDemo : public Demo
{
  public:
    TriangleDemo();
    void Init(GLFWwindow* window) override;
    void Draw(GLFWwindow* window, float deltaTime) override;
    void Unload() override;
    void ProcessKeyboard(GLFWwindow* window, float deltaTime) override;
    bool DrawMenu() override;

  private:
    int fillModePrev = GLFW_RELEASE, fillMode = GLFW_RELEASE;
    int lineModePrev = GLFW_RELEASE, lineMode = GLFW_RELEASE;

    Shader shader;
    GLuint vaoHandle;
    GLuint vboHandles[3];
    unsigned int EBO;
};

#endif
