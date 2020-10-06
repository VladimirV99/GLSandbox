#include "hdrBloomDemo.hpp"

HdrBloomDemo::HdrBloomDemo() :
    shader("../assets/hdrBloom.vert.glsl", "../assets/hdrBloom.frag.glsl"),
    shaderLight("../assets/hdrBloom.vert.glsl", "../assets/lightBox.frag.glsl"),
    shaderBlur("../assets/blur.vert.glsl", "../assets/blur.frag.glsl"),
    shaderBloomFinal("../assets/hdrBloomFinal.vert.glsl", "../assets/hdrBloomFinal.frag.glsl")
{ }

void HdrBloomDemo::Init(GLFWwindow* window)
{
    
}

void HdrBloomDemo::Draw(GLFWwindow* window)
{
    
}

void HdrBloomDemo::renderQuad()
{
    
}

void HdrBloomDemo::Unload()
{
    
}

void HdrBloomDemo::processKeyboard(GLFWwindow *window)
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

void HdrBloomDemo::processMouse(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset)
{
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void HdrBloomDemo::processScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}