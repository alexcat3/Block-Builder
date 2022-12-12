//
// Created by alexc on 11/10/2022.
//

#ifndef GLFW_TEST_SCREENOBJECT_H
#define GLFW_TEST_SCREENOBJECT_H
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "glm/glm.hpp"

//Represents a 3D object which is drawn on screen
class ScreenObject{
    //The triangle and vertex data for the object
    VertexArray vertexArr;
    //The texture used to color the object
    Texture texture;
    //The object's position
    glm::vec3 pos;
    //A matrix representing the object's rotation and scale
    glm::mat4 rotationModel;
    //Controls if the object is be displayed with inverted colors
    bool invert;

public:
    ScreenObject(VertexArray vertexArr, Texture texture, glm::vec3 position);
    //Rotate the object
    void rotateDeg(float deg, glm::vec3 axis);
    void rotateRad(float rad, glm::vec3 axis);
    //Move the object by an offset
    void move(glm::vec3 direction);
    //Change the object's position
    void setPos(glm::vec3 pos);
    //Draw the object's position
    void draw();
    glm::vec3 getPos();
    //Set whether the object is displayed with inverted colors
    void setInvert(bool invert);
    glm::mat4 getModel();
    Texture getTexture();
};


#endif //GLFW_TEST_SCREENOBJECT_H
