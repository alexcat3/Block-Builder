//
// Created by alexc on 11/10/2022.
//

#include "ScreenObject.h"
#include "glm/gtc/matrix_transform.hpp"

ScreenObject::ScreenObject( ElementBufferObject EBO, Texture texture, glm::mat4 model):
  EBO(EBO), texture(texture), model(model){};
ScreenObject::ScreenObject( ElementBufferObject EBO, Texture texture, float scale, glm::vec3 position):
    EBO(EBO), texture(texture), model(glm::translate(glm::scale(glm::mat4(1),glm::vec3(scale)), position)){};

void ScreenObject::rotateDeg(float deg, glm::vec3 axis) {
    rotateRad(glm::radians(deg),axis);
}
void ScreenObject::rotateRad(float rad, glm::vec3 axis) {
    model = glm::rotate(model, rad, axis);
}

void ScreenObject::move(glm::vec3 direction){
    model = glm::translate(model, direction);
}

void ScreenObject::scale(glm::vec3 factor){
    model = glm::scale(model, factor);
}
void ScreenObject::scale(float factor){
    scale(glm::vec3(factor));
}

void ScreenObject::draw(){
    Shader::currentShader->setUniform("model", model);
    texture.bind();
    EBO.bindVertexArray();
    glDrawElements(GL_TRIANGLES, EBO.getTriangleDataLen(), GL_UNSIGNED_INT, 0);
}

