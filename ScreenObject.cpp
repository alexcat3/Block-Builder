//
// Created by alexc on 11/10/2022.
//

#include "ScreenObject.h"
#include "glm/gtc/matrix_transform.hpp"

ScreenObject::ScreenObject(VertexArray vertexArr, Texture texture, glm::mat4 model):
  vertexArr(vertexArr), texture(texture), model(model){};
ScreenObject::ScreenObject(VertexArray vertexArr, Texture texture, float scale, glm::vec3 position):
    vertexArr(vertexArr), texture(texture), model(glm::translate(glm::scale(glm::mat4(1),glm::vec3(scale)), position*(1/scale))){};

void ScreenObject::rotateDeg(float deg, glm::vec3 axis) {
    rotateRad(glm::radians(deg),axis);
}
void ScreenObject::rotateRad(float rad, glm::vec3 axis) {
    model = glm::rotate(model, rad, axis);
}

void ScreenObject::move(glm::vec3 direction){
    model = glm::translate(model, direction/getScale());
}

void ScreenObject::scale(glm::vec3 factor){
    model = glm::scale(model, factor);
}
void ScreenObject::scale(float factor){
    scale(glm::vec3(factor));
}
float ScreenObject::getScale(){
    return glm::length(glm::vec4(1,0,0,1)*model);
}

glm::vec3 ScreenObject::getPos(){
    return glm::vec4(0,0,0,1)*model;
}

void ScreenObject::draw(){
    Shader::currentShader->setUniform("model", model);
    texture.bind();
    vertexArr.bind();
    glDrawElements(GL_TRIANGLES, vertexArr.getTriangleDataLen(), GL_UNSIGNED_INT, 0);
}

