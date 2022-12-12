//
// Created by alexc on 11/9/2022.
//

#ifndef GLFW_TEST_SHADER_H
#define GLFW_TEST_SHADER_H
#include <iostream>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include <fstream>
#include <optional>

//Represents a compiled shader program
class Shader {
    //Id representing the shader program to opengl
    unsigned int shaderProgram;

    //Compile a shader of a given type using a given source file
    unsigned static int compileShader(unsigned short shaderType, const char* source);
    //Link together multiple compiled shaders into a shader program
    unsigned static int makeShaderProgram(const unsigned int shaders[], int n);
public:
    //Create a new shader program using the given vertex shader source file and fragment shader source file
    Shader(const std::string &vertexPath, const std::string &fragmentPath) noexcept;

    //The shader which is currently enabled
    static Shader *currentShader;

    //Make it so draw commands use this shader program
    void enable();

    //Set a variable that is used by the shader
    void setUniform(const std::string &uniformName, glm::mat4 matrix) const;
    void setUniformInt(const std::string &uniformName, int i) const;
    void setUniformVec3(const std::string &uniformName, glm::vec3 uniform);

    //Standard shaders that can be used
    static std::optional<Shader> BasicColorVertexShader;
    static std::optional<Shader> BasicTextureShader;
    //Compiles the standard shaders
    static void initShaders();
};


#endif //GLFW_TEST_SHADER_H
