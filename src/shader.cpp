#include "shader.hpp"

#include <spdlog/spdlog.h>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    this->ID = createProgram(vertexPath, fragmentPath);
}

std::string Shader::loadAsString(const std::string& path)
{
    std::ifstream in(path);
    if (!in.is_open())
    {
        spdlog::error("Error opening file {}", path);
        exit(EXIT_FAILURE);
    }
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        std::ostringstream sstr;
        sstr << in.rdbuf();
        in.close();
        return sstr.str();
    }
    catch (std::ifstream::failure e)
    {
        spdlog::error("Error reading file {}", path);
        exit(EXIT_FAILURE);
    }
    return "";
}

GLuint Shader::compileShader(const std::string& path, GLenum type)
{
    GLuint shader = glCreateShader(type);
    if (0 == shader)
    {
        spdlog::error("Error creating shader!");
        exit(EXIT_FAILURE);
    }

    std::string shaderCode = loadAsString(path);
    const GLchar* codeArray[] = {shaderCode.c_str()};

    glShaderSource(shader, 1, codeArray, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (GL_FALSE == success)
    {
        spdlog::error("Shader compilation failed!");

        // Get and print the info log
        GLint logLen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0)
        {
            std::string log(logLen, ' ');
            GLsizei written;
            glGetShaderInfoLog(shader, logLen, &written, &log[0]);
            spdlog::error("Shader log:\n{}", log);
        }

        exit(EXIT_FAILURE);
    }

    return shader;
}

GLuint Shader::createProgram(const char* vertexPath, const char* fragmentPath)
{
    // Create the program object using the following code:
    GLuint programHandle = glCreateProgram();
    if (0 == programHandle)
    {
        spdlog::error("Error creating program object.");
        exit(EXIT_FAILURE);
    }

    // Compile shaders
    GLuint vertShader = compileShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);

    // Attach the shaders to the program object as follows:
    glAttachShader(programHandle, vertShader);
    glAttachShader(programHandle, fragShader);

    glLinkProgram(programHandle);

    GLint success;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
    if (GL_FALSE == success)
    {
        spdlog::error("Failed to link shader program!");
        GLint logLen;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0)
        {
            std::string log(logLen, ' ');
            GLsizei written;
            glGetProgramInfoLog(programHandle, logLen, &written, &log[0]);
            spdlog::error("Program log:\n{}", log);
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        glUseProgram(programHandle);
    }

    // Detach and delete shader objects
    glDetachShader(programHandle, vertShader);
    glDetachShader(programHandle, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return programHandle;
}

void Shader::use() { glUseProgram(ID); }

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat4(const std::string& name, glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
};
