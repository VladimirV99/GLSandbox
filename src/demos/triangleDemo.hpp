#ifndef TRIANGLEDEMO_H
#define TRIANGLEDEMO_H

#include "demo.hpp"

class TriangleDemo: public Demo
{
public:
    TriangleDemo();
    void Init(GLFWwindow* window) override;
    void Draw(GLFWwindow* window) override;
    void Unload() override;
private:
    void processInput(GLFWwindow *window);
private:
    int fill_mode_prev = GLFW_RELEASE, fill_mode = GLFW_RELEASE;
    int line_mode_prev = GLFW_RELEASE, line_mode = GLFW_RELEASE;

    Shader shader;
    GLuint vaoHandle;
    GLuint vboHandles[3]; 
    unsigned int EBO;
};

#endif