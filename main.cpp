#include <iostream>
#include <chrono>
#include <thread>
#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Shader.h"
#include "ElementBufferObject.h"
#include "Texture.h"
#include "ScreenObject.h"
#include "Cube.h"

using namespace std;

//Used tutorial https://learnopengl.com/Getting-started/


GLFWwindow* initWindow(int width, int height);
void processInput(GLFWwindow* window);
int main() {
    cout<<"Foo!";
    GLFWwindow* window = initWindow(800,600);
    Shader::initShaders();

    Texture containerTexture("../container.jpg",{});
    Cube cube(containerTexture, .5, glm::vec3(0,0,0));

    //Matrix that represents the position of the camera
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    //Matrix that represents the camera's field of view
    //Creates a frustrum that defines the visual space
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, .1f, 100.0f);

    glEnable(GL_DEPTH_TEST);
    //Main loop
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        cube.rotateDeg(1,glm::vec3(1,0,0));
        //Clear the screen
        glClearColor(1.0,1.0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Shader::BasicTextureShader->enable();
        Shader::BasicTextureShader->setUniform("view", view);
        Shader::BasicTextureShader->setUniform("projection", projection);

        cube.draw();
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}



GLFWwindow* initWindow(int width, int height){
    //Initialize glfw using opengl 3.3 and the core profile
    //(The core profile is a more modern version of opengl that removes outdated functions for higher performance)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a new 800x600 window
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    //If we couldn't create the window, raise an error and quit
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    //Initialize GLAD to get OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
    //Tell OpenGL the window size
    glViewport(0, 0, width, height);

    return window;
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
