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
//Must be used with the colored vertex shader
class Rect2D {
    VertexArray verticies;
    glm::vec3 color;
    Texture texture;
public:
    Rect2D(float x1, float y1, float x2, float y2, float z, Texture texture);
    void draw();
    void setTexture(Texture t);
};


#endif //GLFW_TEST_RECT2D_H
