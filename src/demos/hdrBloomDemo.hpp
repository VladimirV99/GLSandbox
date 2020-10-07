#ifndef HDR_BLOOM_DEMO_H
#define HDR_BLOOM_DEMO_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

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
    void DrawMenu() override;
private:
    void renderQuad();
    void renderCube();
private:
    Shader shader, shaderLight, shaderBlur, shaderBloomFinal;

    // camera
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f));

    // lighting
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;

    unsigned int quadVBO, quadVAO = 0;
    unsigned int cubeVBO, cubeVAO = 0;
    unsigned int woodTexture, containerTexture;
    unsigned int hdrFBO;
    unsigned int colorBuffers[2];
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];

    bool bloom = true, bloomKeyPressed = false;
    float exposure = 1.0f;
};

#endif