#ifndef NORMALMAPDEMO_H
#define NORMALMAPDEMO_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "demo.hpp"
#include "../camera.hpp"
#include "../shader.hpp"

class NormalMapDemo: public Demo
{
public:
    NormalMapDemo();
    void Init(GLFWwindow* window) override;
    void Draw(GLFWwindow* window, float deltaTime) override;
    void Unload() override;
    void ProcessKeyboard(GLFWwindow *window, float deltaTime) override;
    void ProcessMouse(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset) override;
    void ProcessScroll(GLFWwindow* window, double xoffset, double yoffset) override;
    bool DrawMenu() override;
private:
    void RenderQuad();
private:
    Shader shader;

    // camera
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // lighting
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    unsigned int VBO, VAO = 0;
    unsigned int diffuseMap, normalMap;
};

#endif