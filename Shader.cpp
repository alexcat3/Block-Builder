//
// Created by alexc on 11/9/2022.
//

#include "Shader.h"
#include <exception>
#include "glm/gtc/type_ptr.hpp"

unsigned int Shader::compileShader(unsigned short shaderType, const char* source){
    //Try to compile the shader
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    //If the compile failed, display an error message and quit the program
    int success;
    char compileError[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, compileError);
        std::cout<<"ERROR::SHADER::COMPILATION_FAILED\n"<<compileError<<std::endl;
        std::cout<<"Source:\n"<<source<<std::endl;
        exit(1);
    }
    //If it was successful return the shader's id
    return shader;
}

//Links together several shaders to create a shader program
unsigned int Shader::makeShaderProgram(const unsigned int shaders[], int n){
    //Try to link the shaders together
    unsigned int shaderProgram = glCreateProgram();
    for(int i=0; i<n; i++){
        glAttachShader(shaderProgram, shaders[i]);
    }
    glLinkProgram(shaderProgram);
    //If linking failed display an error message and exit
    int success;
    char compileError[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, compileError);
        std::cout<<"ERROR::SHADER::LINKING FAILED\n"<<compileError<<std::endl;
        exit(1);
    }
    //Otherwise return the shader program's id
    return shaderProgram;
}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) noexcept{
    //Read source code into strings
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    std::ifstream vertexShaderFile(vertexPath);
    if(!vertexShaderFile){
        std::cout<<"Shader source file not found: "<<vertexPath<<std::endl;
        exit(1);
    }
    std::ifstream fragmentShaderFile(fragmentPath);
    if(!fragmentShaderFile){
        std::cout<<"Shader source file not found "<<fragmentPath<<std::endl;
        exit(1);
    }
    try {
        getline(vertexShaderFile, vertexShaderSource, '\0');
        getline(fragmentShaderFile, fragmentShaderSource, '\0');
    }catch(std::exception e){
        std::cout<<e.what()<<std::endl;
    }

    //Compile each shader
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());
    unsigned int shaders[] = {vertexShader, fragmentShader};

    //Link shaders into a shader program
    shaderProgram = makeShaderProgram(shaders,2);
    //Delete original compiled versions (they are no longer needed now that we have the program)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

//Makes it so that drawing commands use this shader
void Shader::enable(){
    currentShader = this;
    glUseProgram(shaderProgram);
}



void Shader::setUniform(std::string uniformName, glm::mat4 matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformInt(std::string uniformName, int i) const {
    glUniform1i(glGetUniformLocation(shaderProgram, uniformName.c_str()), i);
}

std::optional<Shader> Shader::BasicColorVertexShader;
std::optional<Shader> Shader::BasicTextureShader;

void Shader::initShaders(){
    Shader::BasicColorVertexShader = Shader("../shaders/BasicColorVertexVertexShader.shader","../shaders/BasicColorVertexFragShader.shader");

    Shader::BasicTextureShader = Shader("../shaders/BasicTextureVShader.glsl", "../shaders/BasicTextureFShader.glsl");
}

Shader* Shader::currentShader;


