#ifndef HDR_BLOOM_DEMO_H
#define HDR_BLOOM_DEMO_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "demo.hpp"
#include "../common.hpp"
#include "../camera.hpp"

class HdrBloomDemo: public Demo
{
public:
    HdrBloomDemo();
    void Init(GLFWwindow* window) override;
    void Draw(GLFWwindow* window) override;
    void Unload() override;
    void processKeyboard(GLFWwindow *window) override;
    void processMouse(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset) override;
    void processScroll(GLFWwindow* window, double xoffset, double yoffset) override;
private:
    void renderQuad();
    void renderCube();
private:
    Shader shader, shaderLight, shaderBlur, shaderBloomFinal;

    // camera
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f));

    // lighting
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    unsigned int quadVBO, quadVAO = 0;
    unsigned int cubeVBO, cubeVAO = 0;
    unsigned int hdrFBO;
    unsigned int woodTexture, containerTexture;

    bool bloom = true, bloomKeyPressed = false;

    float exposure = 1.0f;

};

#endif