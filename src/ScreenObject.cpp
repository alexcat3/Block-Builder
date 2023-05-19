

#include "ScreenObject.h"
#include "glm/gtc/matrix_transform.hpp"

ScreenObject::ScreenObject(VertexArray vertexArr, Texture texture,  glm::vec3 position):
    vertexArr(vertexArr), texture(texture), rotationModel(glm::mat4(1)), pos(position), invert(false){};

void ScreenObject::rotateDeg(float deg, glm::vec3 axis) {
    rotateRad(glm::radians(deg),axis);
}
void ScreenObject::rotateRad(float rad, glm::vec3 axis) {
    rotationModel = glm::rotate(rotationModel, rad, axis);
}

void ScreenObject::move(glm::vec3 direction){
   pos += direction;
}

glm::vec3 ScreenObject::getPos(){
     return pos;
}

void ScreenObject::setPos(glm::vec3 position){
    pos = position;
}

glm::mat4 ScreenObject::getModel(){
    return glm::translate(glm::mat4(1),pos)*rotationModel;
}
void ScreenObject::draw(){
    Shader::currentShader->setUniform("model", getModel());
    Shader::currentShader->setUniformInt("invert", invert);
    vertexArr.bind();
    texture.bind();
    glDrawElements(GL_TRIANGLES, vertexArr.getTriangleDataLen(), GL_UNSIGNED_INT, 0);
}

Texture ScreenObject::getTexture() {
    return texture;
}

void ScreenObject::setInvert(bool invert) {
    this->invert = invert;
}