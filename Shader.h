//
// Created by alexc on 11/9/2022.
//

#ifndef GLFW_TEST_SHADER_H
#define GLFW_TEST_SHADER_H
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <fstream>
#include <optional>

class Shader {
    unsigned int shaderProgram;

    unsigned static int compileShader(unsigned short shaderType, const char* source);
    unsigned static int makeShaderProgram(const unsigned int shaders[], int n);
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath) noexcept;
    void enable() const;

    //Standard shaders that can be used
    static std::optional<Shader> BasicColorVertexShader;

    //Compiles the standard shaders
    static void initShaders();
};


#endif //GLFW_TEST_SHADER_H
