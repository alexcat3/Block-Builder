//
// Created by alexc on 11/10/2022.
//

#include "ScreenObject.h"
#include "glm/gtc/matrix_transform.hpp"

ScreenObject::ScreenObject(VertexArray vertexArr, Texture texture, glm::mat4 model):
  vertexArr(vertexArr), texture(texture), model(model){};
ScreenObject::ScreenObject(VertexArray vertexArr, Texture texture,  glm::vec3 position):
    vertexArr(vertexArr), texture(texture), model(glm::translate(glm::mat4(1), position)){};

void ScreenObject::rotateDeg(float deg, glm::vec3 axis) {
    rotateRad(glm::radians(deg),axis);
}
void ScreenObject::rotateRad(float rad, glm::vec3 axis) {
    model = glm::rotate(model, rad, axis);
}

void ScreenObject::move(glm::vec3 direction){
    model = glm::translate(model, direction);
}

glm::vec3 ScreenObject::getPos(){
     glm::vec4 posW = model*glm::vec4(0,0,0,1);
     return glm::vec3(posW.x, posW.y, posW.z);
}

void ScreenObject::draw(){
    Shader::currentShader->setUniform("model", model);
    texture.bind();
    vertexArr.bind();
    glDrawElements(GL_TRIANGLES, vertexArr.getTriangleDataLen(), GL_UNSIGNED_INT, 0);
}
