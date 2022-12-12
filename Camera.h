//
// Created by alexc on 12/4/2022.
//

#ifndef GLFW_TEST_CAMERA_H
#define GLFW_TEST_CAMERA_H
#include "glm/glm.hpp"
#include <glad/glad.h>
#include "glfw3.h"
class Camera {
    //The camera's position in the world
    glm::vec3 pos;
    //Matrix representing the camera's field of view and aperature
    glm::mat4 projection;
    //Angle between the camera's direction and the negative z axis, with the negative x axis being pi/2
    //Represents the camera's rotation in the xz plane
    float yawRad;
    //Angle between the camera's direction and the negative y axis
    //Camera's tilt up/down
    float pitchRad;
    //The window
    GLFWwindow *window;
    //Stores the previous mouse coordinates to calculate how much the mouse has moved
    double oldMouseX, oldMouseY;
public:
    Camera(glm::vec3 pos, float fovDeg, float aspect, float zNear, float zFar, GLFWwindow *window);

    //Returns the direction in which the camera is facing
    glm::vec3 getDirection();
    //Returns the position of the camera
    glm::vec3 getPos();
    //Returns the matrix representing the camera's position and rotation
    glm::mat4 getViewMatrix();
    //Gives the camera's position, rotation, and perspective information to the shader
    void prepareDraw3D();
    //Erases the position, rotation, and perspective information from the shader so that 2D menus can be drawn
    void prepareDrawOverlay();
    //Rotate the camera in the XY plane
    void rotateRad(float rad);
    void rotateDeg(float deg);
    //Tilt the camera up or down
    void tiltRad(float rad);
    void tiltDeg(float deg);
    float getPitchRad();
    void move(glm::vec3 direction);
    //Allows the user to rotate and move the camera using the mouse and keyboard
    void takeUserInput();

};


#endif //GLFW_TEST_CAMERA_H
