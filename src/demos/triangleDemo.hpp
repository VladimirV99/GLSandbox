#ifndef TRIANGLEDEMO_H
#define TRIANGLEDEMO_H

#include "demo.hpp"

#include <imgui.h>

class TriangleDemo: public Demo
{
public:
    TriangleDemo();
    void Init(GLFWwindow* window) override;
    void Draw(GLFWwindow* window) override;
    void Unload() override;
    void ProcessKeyboard(GLFWwindow *window) override;
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