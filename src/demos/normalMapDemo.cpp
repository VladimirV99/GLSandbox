#include "normalMapDemo.hpp"

NormalMapDemo::NormalMapDemo() : shader("../assets/normalMap.vert.glsl", "../assets/normalMap.frag.glsl") { }

void NormalMapDemo::Init(GLFWwindow* window)
{
    
}

void NormalMapDemo::Draw(GLFWwindow* window)
{
    
}

void NormalMapDemo::Unload()
{
    
}

void NormalMapDemo::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void NormalMapDemo::processMouse(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset)
{
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void NormalMapDemo::processScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}