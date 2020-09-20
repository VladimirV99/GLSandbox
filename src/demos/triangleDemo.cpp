#include "triangleDemo.hpp"

TriangleDemo::TriangleDemo() : shader("../assets/triangle.vert.glsl", "../assets/triangle.frag.glsl") { }

void TriangleDemo::Init(GLFWwindow* window)
{ 
    // Draw triangle
    float positionData[] = { 
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
        }; 
    float colorData[] = { 
        1.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f
    };
    float texData[] = { 
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };
    unsigned int indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };
    
    // Create and populate the buffer objects
    glGenBuffers(3, vboHandles); 
    GLuint positionBufferHandle = vboHandles[0]; 
    GLuint colorBufferHandle = vboHandles[1];
    GLuint texBufferHandle = vboHandles[2];
    
    // Populate the position buffer 
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle); 
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), 
        positionData, GL_STATIC_DRAW); 
    
    // Populate the color buffer 
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle); 
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), colorData, 
        GL_STATIC_DRAW);

    // Populate the texture coords buffer 
    glBindBuffer(GL_ARRAY_BUFFER, texBufferHandle); 
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), texData, 
        GL_STATIC_DRAW);

    // Create and set-up the vertex array object 
    glGenVertexArrays( 1, &vaoHandle ); 
    glBindVertexArray(vaoHandle); 
    
    // Enable the vertex attribute arrays 
    glEnableVertexAttribArray(0);  // Vertex position 
    glEnableVertexAttribArray(1);  // Vertex color
    glEnableVertexAttribArray(2);  // Tex Coords 
    
    // Map index 0 to the position buffer 
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); 
    
    // Map index 1 to the color buffer 
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Map index 2 to the texture buffer 
    glBindBuffer(GL_ARRAY_BUFFER, texBufferHandle); 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    // Index buffer   
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void TriangleDemo::Draw(GLFWwindow* window)
{
    shader.use();

    // Wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(vaoHandle); // VAO keeps the EBO
    glDrawArrays(GL_TRIANGLES, 0, 3 );
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // square
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // triangle
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void TriangleDemo::Unload()
{
    glDeleteVertexArrays(1, &vaoHandle);
    glDeleteBuffers(1, &vboHandles[0]);
    glDeleteBuffers(1, &vboHandles[1]);
    glDeleteBuffers(1, &vboHandles[2]);
}