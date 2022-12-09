//
// Created by alexc on 12/6/2022.
//

#include "Rect2D.h"
Rect2D::Rect2D(float x1, float y1, float x2, float y2, float z, Texture texture):
    texture(texture),
    verticies(
            std::vector<float>({x1,y1, z, 0,0, x2,y1, z, 1,0, x1,y2, z, 0,1, x2,y2, z,1,1}),
            5,
            std::vector<unsigned int>({0,1,2,3})
            )
    {
        //X Y Z coordinates are a vector of size 3
        verticies.vertexAttrib(0,3);
        //Texture coordinates are a vector of size 2
        verticies.vertexAttrib(1,2);
    };

void Rect2D::draw() {
    texture.bind();
    verticies.bind();
    Shader::currentShader->setUniform("model", glm::mat4(1));
    glDrawElements(GL_TRIANGLE_STRIP,verticies.getTriangleDataLen(),GL_UNSIGNED_INT,0);

}

void Rect2D::setTexture(Texture t){
    texture = t;
}

