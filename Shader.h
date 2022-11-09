//
// Created by alexc on 11/9/2022.
//

#ifndef GLFW_TEST_SHADER_H
#define GLFW_TEST_SHADER_H
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <fstream>

class Shader {
    unsigned int shaderProgram;

    unsigned int compileShader(unsigned short shaderType, const char* source);
    unsigned int makeShaderProgram(const unsigned int shaders[], int n);
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    void enable();
};


#endif //GLFW_TEST_SHADER_H
