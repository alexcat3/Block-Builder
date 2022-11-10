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

using namespace std;

//Used tutorial https://learnopengl.com/Getting-started/



GLFWwindow* initWindow(int width, int height);
void processInput(GLFWwindow* window);
int main() {
    GLFWwindow* window = initWindow(800,600);
    Shader::initShaders();

    vector<float> cube_vertices{
        //x,y,z,tx,ty
        //front face
        -1,-1, 1,0,0,
        -1, 1, 1,0,1,
         1, 1, 1,1,1,
         1,-1, 1,1,0,

         //back face
       -1,-1, -1,0,0,
       -1, 1, -1,0,1,
        1, 1, -1,1,1,
        1,-1, -1,1,0,

        //top face
        -1, 1, 1,0,0,
        -1, 1,-1,0,1,
         1, 1,-1,1,1,
         1, 1, 1,1,0,

         //bottom face
         -1,-1, 1,0,0,
         -1,-1,-1,0,1,
          1,-1,-1,1,1,
          1,-1, 1,1,0,

        //left face
        -1,-1,-1,0,0,
        -1, 1,-1,0,1,
        -1, 1, 1,1,1,
        -1,-1, 1,1,0,



        //right face
        1,-1,-1,0,0,
        1, 1,-1,0,1,
        1, 1, 1,1,1,
        1,-1, 1,1,0
    };

    vector<unsigned int> cube_triangles{
        //Front face
        0,1,2,
        2,3,0,
        //Back face
        4,5,6,
        6,7,4,
        //Top face
        8,9,10,
        10,11,8,
        //Bottom face
        12,13,14,
        14,15,12,
        //Left face
        16,17,18,
        18,19,16,
        //Right face
        20,21,22,
        22,23,20
    };
    ElementBufferObject cube(cube_vertices, 5, cube_triangles);
    cube.vertexAttrib(0,3); //Location is a set of 3 verticies
    cube.vertexAttrib(1,2); //Texture coordinate is a set of 2 verticies

    Texture containerTexture("../container.jpg",{});

    //Matrix that represents the position of the cube
    glm::mat4 cube_model = glm::mat4(1);
    //cube_model = glm::rotate(cube_model, glm::radians(45.0f), glm::vec3(0,0,1));
    cube_model = glm::scale(cube_model, glm::vec3(.25,.25,.25));

    cout<<glm::to_string(cube_model);
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
        cube_model = glm::rotate(cube_model,glm::radians(2.0f),glm::vec3(0,1,0));

        //Clear the screen
        glClearColor(1.0,1.0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Shader::BasicTextureShader->enable();
        Shader::BasicTextureShader->setUniform("view", view);
        Shader::BasicTextureShader->setUniform("projection", projection);

        containerTexture.bind();
        cube.bindVertexArray();
        Shader::BasicTextureShader->setUniform("model", cube_model);
        glDrawElements(GL_TRIANGLES, cube.getTriangleDataLen(), GL_UNSIGNED_INT, 0);

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
