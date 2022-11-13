#include <iostream>
#include <chrono>
#include <thread>
#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include <map>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "ScreenObject.h"
#include "Cube.h"
#include "ThreeDVec.h"
#include "ThreeDVec.cpp"

using namespace std;

//Used tutorial https://learnopengl.com/Getting-started/


GLFWwindow* initWindow(int width, int height);

int main() {
    //Create new OpenGL window
    GLFWwindow* window = initWindow(800,600);
    //Compile the shaders used in the project
    Shader::initShaders();
    float cubeScale = 1;
    ThreeDVec<optional<Cube>> world(32,8,32);

    Texture stone("../textures/stone.png", {});

    //Create a "floor" for the world out of stone
    for(int x=0; x<world.getDimensions().x; x++){
        for(int z=0; z<world.getDimensions().z; z++){
            world.at(x,0,z) = Cube(stone, cubeScale, glm::vec3(x,0,z));
        }
    }

    Texture cursorTex("../textures/cursor.png",{});
    Cube cursor(cursorTex, cubeScale, glm::vec3(0,0,0));

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
        //***Process user input

        //Space moves camera up, left shift moves it down
        if(glfwGetKey(window, GLFW_KEY_SPACE)){
            view = glm::translate(view, glm::vec3(0, -.1,0));
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)){
            view = glm::translate(view, glm::vec3(0,.1,0));
        }

        //WASD keys move the camera in x and z directions
        if(glfwGetKey(window, GLFW_KEY_W)){
            view = glm::translate(view, glm::vec3(0,0,.1));
        }
        if(glfwGetKey(window, GLFW_KEY_S) ) {
            view = glm::translate(view, glm::vec3(0,0,-.1));
        }
        if(glfwGetKey(window, GLFW_KEY_A)){
            view = glm::translate(view, glm::vec3(.1,0,0));
        }
        if(glfwGetKey(window, GLFW_KEY_D)){
            view = glm::translate(view, glm::vec3(-.1,0,0));
        }
        //QE keys rotate the camera
        if(glfwGetKey(window, GLFW_KEY_Q)){
            projection = glm::rotate(projection, glm::radians(-3.0f),glm::vec3(0,1,0));
        }
        if(glfwGetKey(window, GLFW_KEY_E)){
            projection = glm::rotate(projection, glm::radians(3.0f), glm::vec3(0,1,0));
        }

        //Arrow keys move cursor in x and z directions
        if(glfwGetKey(window, GLFW_KEY_UP) && cursor.getPos().z > 0){
            cursor.move(glm::vec3(0,0,-cubeScale));
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN) && cursor.getPos().z < (world.getDimensions().z-1)*cubeScale){
            cursor.move(glm::vec3(0,0,cubeScale));
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT) && cursor.getPos().x > 0){
            cursor.move(glm::vec3(-cubeScale,0,0));
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT) && cursor.getPos().x < (world.getDimensions().x-1) * cubeScale){
            cursor.move(glm::vec3(cubeScale,0,0));
        }
        //Right shift and right control move the cursor up and down
        if(glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) && cursor.getPos().y > 0){
            cursor.move(glm::vec3(0,0,-cubeScale));
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) && cursor.getPos().y < (world.getDimensions().x-1) * cubeScale) {
            cursor.move(glm::vec3(0, 0, cubeScale));
        }

        //Clear the screen with cyanS
        glClearColor(0,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Pass the camera position and perspective to the shader
        Shader::BasicTextureShader->enable();
        Shader::BasicTextureShader->setUniform("view", view);
        Shader::BasicTextureShader->setUniform("projection", projection);

        cout<<glm::to_string(cursor.getPos()/cubeScale);

        for(int x=0; x<world.getDimensions().x; x++){
            for(int y=0; y<world.getDimensions().y; y++){
                for(int z=0; z<world.getDimensions().z; z++){
                    if(glm::vec3(x,y,z) == cursor.getPos()/cubeScale){
                        cursor.draw();
                    }else if(world.at(x,y,z) != nullopt){
                        world.at(x,y,z)->draw();
                    }
                }
            }
        }
        //Display drawn objects on screen
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
