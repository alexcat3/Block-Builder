//
// Created by alexc on 11/10/2022.
//

#ifndef GLFW_TEST_SCREENOBJECT_H
#define GLFW_TEST_SCREENOBJECT_H
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "glm/glm.hpp"


class ScreenObject{
    VertexArray vertexArr;
    Texture texture;
    glm::mat4 model;


public:
    ScreenObject(VertexArray vertexArr, Texture texture, glm::mat4 model);
    ScreenObject(VertexArray vertexArr, Texture texture, float scale, glm::vec3 position);

    void rotateDeg(float deg, glm::vec3 axis);
    void rotateRad(float rad, glm::vec3 axis);

    void move(glm::vec3 direction);
    void scale(float factor);
    void scale(glm::vec3 factor);

    float getScale();
    void draw();
    glm::vec3 getPos();

};


#endif //GLFW_TEST_SCREENOBJECT_H
