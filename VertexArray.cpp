//
// Created by alexc on 11/9/2022.
//

#include "VertexArray.h"
#include <glad/glad.h>
#include <glfw3.h>

VertexArray::VertexArray(const std::vector<float> &vertices, int vertexLen, const std::vector<unsigned int> &triangleData) {
    numVertices = vertices.size();
    triangleDataLen = triangleData.size();
    this->vertexLen = vertexLen;
    currentVarOffset = 0;

    //Create vertex array object
    //Represents the structure of the data in the vertex array
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Create buffers
    //VBO stores the vertex data, EBO stores the triangle data
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Bind the vertex buffer so we can copy data to it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Bind the element array buffer to the vertex buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //Copy the vertex and triangle data into the buffers
    glBufferData(GL_ARRAY_BUFFER, numVertices*vertexLen*sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleDataLen*sizeof(float), &triangleData[0], GL_STATIC_DRAW);
}

void VertexArray::bind() const{
    glBindVertexArray(VAO);
}

int VertexArray::getNumVertices() const{
    return numVertices;
}

int VertexArray::getTriangleDataLen() const{
    return triangleDataLen;
}

VertexArray* VertexArray::vertexAttrib(int n, int length) {
    glBindVertexArray(VAO);
    glVertexAttribPointer(n, length, GL_FLOAT, GL_FALSE, vertexLen*sizeof(float), (void*)currentVarOffset);
    glEnableVertexAttribArray(n);
    currentVarOffset += length*sizeof(float);
    return this;
}