#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <stb_image.h>
#include <vector>
#include "Shader.h"
#include "ElementBufferObject.h"

using namespace std;

//Used tutorial https://learnopengl.com/Getting-started/



GLFWwindow* initWindow(int width, int height);
void processInput(GLFWwindow* window);
int main() {
    GLFWwindow* window = initWindow(800,600);
    Shader::initShaders();
    //vertex data for square
    vector<float> vertices = {
            // x, y, z, r, g, b
            0.5, 0.5, 0, 1, 0, 0,
            0.5, -.5, 0, 0, 1, 0,
            -.5, -.5 ,0, 0, 0, 1,
            -.5, 0.5, 0, 1, 1, 1,
    };
    int vertexLen = 6;

    vector<unsigned int> triangles{
        0,1,3, //first triangle
        1,2,3 //second triangle
    };


    ElementBufferObject buffer(vertices, vertexLen, triangles);
    //Each vertex's position is a set of 3 floats
    buffer.vertexAttrib(0, 3);
    //Each vertex's color is a set of 3 floats
    buffer.vertexAttrib(1, 3);


    //Main loop
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        //Clear the screen
        glClearColor(1.0,1.0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw the triangle
        Shader::BasicColorVertexShader->enable();
        buffer.bindVertexArray();
        glDrawElements(GL_TRIANGLES, buffer.getTriangleDataLen(), GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
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
