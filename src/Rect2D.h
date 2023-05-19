//
// Created by alexc on 12/6/2022.
//

#ifndef GLFW_TEST_RECT2D_H
#define GLFW_TEST_RECT2D_H
#include "VertexArray.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "Texture.h"

//Draws a 2d rectangle
class Rect2D {
    //The geometry data for the rectangle
    VertexArray verticies;
    //The texture that colors it
    Texture texture;
public:
    //Creates a rectangle with a top left corner at x1,y1 and a bottom right corner at x2,y2, colored with texture texture
    //The z coordinate positions it behind or in front of other objects
    //The top left corner of the screen is (-1,1) and the bottom right corner is (1,-1)
    Rect2D(float x1, float y1, float x2, float y2, float z, Texture texture);
    //Draw the rectangle on the screen
    void draw();
    //Change the rectangle's texture
    void setTexture(Texture t);
};


#endif //GLFW_TEST_RECT2D_H
