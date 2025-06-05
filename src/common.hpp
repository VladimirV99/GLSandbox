#ifndef COMMON_H
#define COMMON_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <string>

// settings
#define SCR_WIDTH 1280
#define SCR_HEIGHT 720

extern GLuint loadTexture(const std::string& path, bool gammaCorrection = false);

#endif
