//
// Created by alexc on 11/9/2022.
//

#ifndef GLFW_TEST_ELEMENTBUFFEROBJECT_H
#define GLFW_TEST_ELEMENTBUFFEROBJECT_H
#include <vector>

class ElementBufferObject {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    int numVertices;
    int triangleDataLen;
    int vertexLen;
    std::size_t currentVarOffset;

public:
    ElementBufferObject(const std::vector<float> &vertices, int vertexLen, const std::vector<unsigned int> &triangleData);
    void bindVertexArray() const;
    int getNumVertices() const;
    int getTriangleDataLen() const;
    void vertexAttrib(int n, int size);
};


#endif //GLFW_TEST_ELEMENTBUFFEROBJECT_H
