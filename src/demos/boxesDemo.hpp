#ifndef BOXESDEMO_H
#define BOXESDEMO_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "demo.hpp"
#include "../common.hpp"
#include "../camera.hpp"

class BoxesDemo: public Demo
{
public:
    BoxesDemo();
    void Init(GLFWwindow* window) override;
    void Draw(GLFWwindow* window) override;
    void Unload() override;
    void processKeyboard(GLFWwindow *window) override;
    void processMouse(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset) override;
    void processScroll(GLFWwindow* window, double xoffset, double yoffset) override;
private:
    Shader shader;

    // camera
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // lighting
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    unsigned int VBO, VAO;
    unsigned int texture;
};

#endif