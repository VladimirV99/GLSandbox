#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

// settings
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

// timing
extern float deltaTime;
extern float lastFrame;

extern float lastX;
extern float lastY;
extern bool firstMouse;

extern void glfw_error_callback(int error, const char* description);
extern void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);

extern GLuint load_texture(const std::string& path, bool gammaCorrection = false);

#endif