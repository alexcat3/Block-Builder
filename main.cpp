#include <iostream>
#include <chrono>
#include <thread>
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "CubeIdenticalFace.h"
#include "Cube4Face.h"
#include "World.h"
#include "BlockSelector.h"

using namespace std;

//Used tutorial https://learnopengl.com/Getting-started/
//Textures from https://github.com/Athemis/PixelPerfectionCE/tree/master/assets/minecraft

GLFWwindow* initWindow(int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
bool leftButtonPress = false;
bool rightButtonPress = false;

BlockSelector* selectorPtr;
int main() {
    //Create new OpenGL window
    GLFWwindow* window = initWindow(800,600);

    glfwSetKeyCallback(window,keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    //Compile the shaders used in the project
    Shader::initShaders();
    float cubeScale = 1;
    //Load cube textures
    CubeIdenticalFace::initCubes();
    Cube4Face::initCubes();

    World world("../world.wld");

    BlockSelector selector;
    selectorPtr = &selector;

    Texture cursorTex("../textures/cursor.png",{});
    CubeIdenticalFace cursor("Cursor", -1, cursorTex, glm::vec3(0, 0, 0));

    //Create a camera
    Camera camera(glm::vec3(-2,0,0),45,800.0f/600.0f, 0.1f, 100.0f, window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    bool cursorHidden;

    bool menuEnabled = false;

    //Main loop
    while(!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        //***Process user input
        //rotate/move camera using mouse + keyboard
        camera.takeUserInput();
        //Move cursor to the place where the camera is looking
        cursorHidden = true;
        std::optional<CameraTarget> target = world.findCameraTarget(camera);
        if(target){
            if(leftButtonPress && world.inBounds(target->addPos)){
                leftButtonPress = false;
                world.at(target->addPos) = selector.getSelectedBlock(glm::vec3(target->addPos));
            }else if(rightButtonPress){
                rightButtonPress = false;
                world.at(target->deletePos) = nullptr;
            }else {
                cursor.setPos(target->addPos);
                cursorHidden = false;
            }
        }



        //Clear the screen with cyan
        glClearColor(0,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Pass the camera position and perspective to the shader
        Shader::BasicTextureShader->enable();
        camera.prepareDraw3D();
        //Draw world and cursor
        world.draw(camera.getPos());
        if(!cursorHidden) {
            cursor.draw();
        }

        //Prepare to draw 2D objects by taking away perspective informaiton
        camera.prepareDrawOverlay();
        //Draw menu if enabled
        selector.draw();
        //Display drawn objects on screen
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
        glfwPollEvents();

    }
    world.saveToFile("../world.wld");
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

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
   selectorPtr->processKbdInput(key, action);
}
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS){
        leftButtonPress = true;
    }else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        rightButtonPress = true;
    }
}