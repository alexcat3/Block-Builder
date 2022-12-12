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
#include "InitWindow.cpp"

using namespace std;

//Used tutorial https://learnopengl.com/Getting-started/
//Textures from https://github.com/Athemis/PixelPerfectionCE/tree/master/assets/minecraft

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
    //Initialize the world-- a giant 3d array of blocks with some helpful methods
    //If the save file exists, this line loads from the file
    World world("../world.wld");

    BlockSelector selector;
    selectorPtr = &selector;

    //Create the cursor block-- a block which appears where the camera is looking to show you where a block will
    //be placed if you click
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
        //Find where camera is looking, handle moving cursor and adding/removing blocks
        cursorHidden = true;
        std::optional<CameraTarget> target = world.findCameraTarget(camera);
        if(target){
            //If the left mouse button is pressed, add a block where the camera is looking
            if(leftButtonPress && world.inBounds(target->addPos)){
                leftButtonPress = false;
                world.at(target->addPos) = selector.getSelectedBlock(glm::vec3(target->addPos));
            }
            //If the right mouse button is pressed, delete a block where the camera is looking
            else if(rightButtonPress){
                rightButtonPress = false;
                world.at(target->deletePos) = nullptr;
            }else {
                //Move cursor to the place where the camera is looking
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

        //Prepare to draw 2D objects by taking away perspective information
        camera.prepareDrawOverlay();
        //Draw hotbar and menu (if enabled)
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