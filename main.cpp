#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
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

    vector<float> rect1_vertices = {
            // x, y, z, r, g, b
            0.5, 0.5, 0, 1, 0, 0,
            0.5, -.5, 0, 0, 1, 0,
            -.5, -.5 ,0, 0, 0, 1,
            -.5, 0.5, 0, 1, 1, 1,
    };
    int rect1_vertexLen = 6;
    vector<unsigned int> rect1_triangles{
        0,1,3, //first triangle
        1,2,3 //second triangle
    };
    ElementBufferObject rect1(rect1_vertices, rect1_vertexLen, rect1_triangles);
    //Each vertex's position is a set of 3 floats
    rect1.vertexAttrib(0, 3);
    //Each vertex's color is a set of 3 floats
    rect1.vertexAttrib(1, 3);

    vector<float> rect2_vertices{
        //x,y,z,tx,ty
        -1, 1,0,0,1,
         1, 1,0,1,1,
         1,-1,0,1,0,
        -1,-1,0,0,0
    };
    vector<unsigned int> rect2_triangles{
        0,1,2,
        3,0,2
    };
    ElementBufferObject rect2(rect2_vertices,5,rect2_triangles);
    //Each vertex's position is a set of 3 floats
    rect2.vertexAttrib(0,3);
    //Each vertex's texture position is a set of 2 floats
    rect2.vertexAttrib(1,2);

    Texture containerTexture("../container.jpg",{});
    containerTexture.bind();

    //Create a transformation for rect2
    //It scales it down to 25% of its size and rotates it around the z axis
    glm::vec4 vec(1, 0, 0, 1);
    glm::mat4 rect2_trans = glm::mat4(1.0);
    rect2_trans = glm::scale(rect2_trans, glm::vec3(.25,.25,.25));
    rect2_trans = glm::rotate(rect2_trans, glm::radians(45.0f), glm::vec3(0,0,1));

    //Main loop
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        //Clear the screen
        glClearColor(1.0,1.0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw the triangle
        Shader::BasicColorVertexShader->enable();
        rect1.bindVertexArray();
        glDrawElements(GL_TRIANGLES, rect1.getTriangleDataLen(), GL_UNSIGNED_INT, 0);

        Shader::BasicTextureShader->enable();
        containerTexture.bind();
        rect2.bindVertexArray();
        Shader::BasicTextureShader->setUniform("transform", rect2_trans);
        glDrawElements(GL_TRIANGLES, rect2.getTriangleDataLen(), GL_UNSIGNED_INT, 0);


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
