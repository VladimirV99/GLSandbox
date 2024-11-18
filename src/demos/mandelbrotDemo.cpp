#include "mandelbrotDemo.hpp"

#include <vector>
#include <algorithm>

MandelbrotDemo::MandelbrotDemo() : shader("../assets/mandelbrot.vert.glsl", "../assets/mandelbrot.frag.glsl"){

}

void MandelbrotDemo::Init(GLFWwindow* window)
{
    float vertices[] = 
    {
    //    x      y      z   
        -1.0f, -1.0f, -0.0f,
        1.0f,  1.0f, -0.0f,
        -1.0f,  1.0f, -0.0f,
        1.0f, -1.0f, -0.0f
    };

    unsigned int indices[] = 
    {
    //  2---,1
    //  | .' |
    //  0'---3
        0, 1, 2,
        0, 3, 1
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
 
    glBindVertexArray(VAO);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static glm::vec4 find_ranges(std::vector<float> &data) 
{
    std::sort(data.begin(), data.end());
    int lowest = 0;
    while (data[lowest] == 0.0f)
    {
        ++lowest;
    }
 
    int size = data.size();
    int length = size - lowest;
    glm::vec4 ranges = glm::vec4( data[lowest], data[lowest + length * 3 / 4 - 1], data[lowest + length * 7 / 8 - 1], data[size - 1] );
    return ranges;
}

void MandelbrotDemo::Draw(GLFWwindow* window, float deltaTime)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // countFPS();

    shader.use();
    shader.setFloat("zoom", zoom);
    shader.setFloat("center_x", center_x);
    shader.setFloat("center_y", center_y);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MandelbrotDemo::Unload()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void MandelbrotDemo::ProcessKeyboard(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        center_y = center_y + 0.01f * zoom;
        if (center_y > 1.0f)
        {
            center_y = 1.0f;
    }
    }
 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        center_y = center_y - 0.01f * zoom;
        if (center_y < -1.0f)
        {
            center_y = -1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        center_x = center_x - 0.01f * zoom;
        if (center_x < -1.0f)
        {
            center_x = -1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        center_x = center_x + 0.01f * zoom;
        if (center_x > 1.0f)
        {
            center_x = 1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        zoom = zoom * 1.02f;
        if (zoom > 1.0f)
        {
            zoom = 1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        zoom = zoom * 0.98f;
        if (zoom < 0.00001f)
        {
            zoom = 0.00001f;
        }
    }
}

void MandelbrotDemo::ProcessMouse(GLFWwindow* window, double xpos, double ypos, double xoffset, double yoffset)
{
}

void MandelbrotDemo::ProcessScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    // zoom += yoffset * 0.1f;
}

bool MandelbrotDemo::DrawMenu()
{
    return true;
}