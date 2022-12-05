//
// Created by alexc on 12/4/2022.
//
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"
Camera::Camera(glm::vec3 pos, float fov, float aspect, float zNear, float zFar, GLFWwindow* window) : window(window), pos(pos), yawRad(0.0f), pitchRad(0.0f),
    projection(glm::perspective(fov, aspect, zNear, zFar)){
    glfwSetInputMode(window,GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Camera::prepareDraw(){
    glm::vec3 yAxis = glm::vec3(0,1,0);
    glm::mat4 view = glm::lookAt(pos, pos+getDirection(), yAxis);

    Shader::currentShader->setUniform("view",view);
    Shader::currentShader->setUniform("projection",projection);
}

glm::vec3 Camera::getDirection(){
    return glm::vec3(cos(pitchRad)*cos(yawRad), sin(pitchRad), cos(pitchRad)*sin(yawRad));
}

void Camera::rotateRad(float rad){
    yawRad += rad;
}
void Camera::rotateDeg(float deg) {
    yawRad += glm::radians(deg);
}

void Camera::tiltRad(float rad) {
    if(pitchRad + rad < M_PI/2 && pitchRad + rad >= -M_PI/2) {
        pitchRad += rad;
    }
}
void Camera::tiltDeg(float deg) {
    tiltRad(glm::radians(deg));
}
void Camera::move(glm::vec3 direction){
    pos += direction;
}

glm::vec3 Camera::getPos(){
    return pos;
}

void Camera::takeUserInput() {
    //Rotate and tilt using mouse input

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    double dX = xPos-oldMouseX;
    double dY = yPos-oldMouseY;
    oldMouseX = xPos;
    oldMouseY = yPos;

    rotateDeg(dX*.5);
    tiltDeg(-dY*.5);

    //Space moves camera up, left shift moves it down
    if(glfwGetKey(window, GLFW_KEY_SPACE)){
        move(glm::vec3(0,1,0));
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)){
        move(glm::vec3(0,-1,0));
    }

    //WS keys move the camera forward and back
    if(glfwGetKey(window, GLFW_KEY_W)){
        move(glm::normalize(getDirection()*glm::vec3(1,0,1)));
    }
    else if(glfwGetKey(window, GLFW_KEY_S) ) {
        move(-glm::normalize(getDirection()*glm::vec3(1,0,1)));
    }
    //AD keys move the camera left and right
    if(glfwGetKey(window, GLFW_KEY_A)){
        move(-glm::cross(getDirection(),glm::vec3(0,1,0)));
    }
    else if(glfwGetKey(window, GLFW_KEY_D)){
        move(glm::cross(getDirection(), glm::vec3(0,1,0)));
    }
}