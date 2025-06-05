#ifndef MANDELBROTDEMO_H
#define MANDELBROTDEMO_H

#include "demo.hpp"
#include "shader.hpp"

class MandelbrotDemo : public Demo
{
  public:
    MandelbrotDemo();
    void Init(GLFWwindow* window) override;
    void Draw(GLFWwindow* window, float deltaTime) override;
    void Unload() override;
    void ProcessKeyboard(GLFWwindow* window, float deltaTime) override;
    void ProcessMouse(GLFWwindow* window, double xpos, double ypos, double xoffset,
                      double yoffset) override;
    void ProcessScroll(GLFWwindow* window, double xoffset, double yoffset) override;
    bool DrawMenu() override;

  private:
    Shader shader;
    unsigned int VAO, VBO, EBO;

    float center_x{0.0f};
    float center_y{0.0f};
    float zoom{1.0};
};

#endif
