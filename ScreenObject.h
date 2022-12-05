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
    glm::vec3 pos;
    glm::mat4 model;
    bool invert;

public:
    ScreenObject(VertexArray vertexArr, Texture texture, glm::vec3 position);

    void rotateDeg(float deg, glm::vec3 axis);
    void rotateRad(float rad, glm::vec3 axis);

    void move(glm::vec3 direction);
    void setPos(glm::vec3 pos);

    void draw();
    glm::vec3 getPos();

    void setInvert(bool invert);

    Texture getTexture();
};


#endif //GLFW_TEST_SCREENOBJECT_H
