//
// Created by alexc on 11/9/2022.
//

#include "Shader.h"

unsigned int Shader::compileShader(unsigned short shaderType, const char* source){
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
    return shader;
}

unsigned int Shader::makeShaderProgram(const unsigned int shaders[], int n){
    unsigned int shaderProgram = glCreateProgram();
    for(int i=0; i<n; i++){
        glAttachShader(shaderProgram, shaders[i]);
    }
    glLinkProgram(shaderProgram);
    int success;
    char compileError[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, compileError);
        std::cout<<"ERROR::SHADER::LINKING FAILED\n"<<compileError<<std::endl;
        exit(1);
    }
    return shaderProgram;
}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath){
    //Read source code into strings
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    std::ifstream vertexShaderFile(vertexPath);
    std::ifstream fragmentShaderFile(fragmentPath);
    getline(vertexShaderFile, vertexShaderSource, '\0');
    getline(fragmentShaderFile, fragmentShaderSource, '\0');

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());
    unsigned int shaders[] = {vertexShader, fragmentShader};
    shaderProgram = makeShaderProgram(shaders,2);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::enable(){
    glUseProgram(shaderProgram);
}


