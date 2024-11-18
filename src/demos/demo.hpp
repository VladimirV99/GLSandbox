#ifndef DEMO_H
#define DEMO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Demo
{
public:
    virtual ~Demo() = default;
    virtual void Init(GLFWwindow* window) = 0;
    virtual void Draw(GLFWwindow* window, float deltaTime) = 0;
    virtual void Unload() = 0;
    virtual void ProcessKeyboard(GLFWwindow* window, float deltaTime) {}
    virtual void ProcessMouse(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset) {}
    virtual void ProcessScroll(GLFWwindow* window, double xoffset, double yoffset) {}
    virtual bool DrawMenu() { return false; }
};

#endif