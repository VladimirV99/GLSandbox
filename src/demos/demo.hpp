#ifndef DEMO_H
#define DEMO_H

#include <stdio.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../shader.hpp"

class Demo
{
public:
    virtual void Init(GLFWwindow* window) = 0;
    virtual void Draw(GLFWwindow* window) = 0;
    virtual void Unload() = 0;
    virtual void ProcessKeyboard(GLFWwindow* window) {}
    virtual void ProcessMouse(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset) {}
    virtual void ProcessScroll(GLFWwindow* window, double xoffset, double yoffset) {}
    virtual bool DrawMenu() { return false; }
};

#endif