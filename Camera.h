//
// Created by alexc on 12/4/2022.
//

#ifndef GLFW_TEST_CAMERA_H
#define GLFW_TEST_CAMERA_H
#include "glm/glm.hpp"
#include <glad/glad.h>
#include "glfw3.h"
class Camera {
    glm::vec3 pos;
    glm::mat4 projection;
    float yawRad;
    float pitchRad;
    GLFWwindow *window;
    double oldMouseX, oldMouseY;
public:
    Camera(glm::vec3 pos, float fovDeg, float aspect, float zNear, float zFar, GLFWwindow *window);

    glm::vec3 getDirection();
    glm::vec3 getPos();
    glm::mat4 getViewMatrix();
    void prepareDraw3D();
    void prepareDrawOverlay();
    void rotateRad(float rad);
    void rotateDeg(float deg);
    void tiltRad(float rad);
    void tiltDeg(float deg);
    void move(glm::vec3 direction);

    void takeUserInput();

};


#endif //GLFW_TEST_CAMERA_H
