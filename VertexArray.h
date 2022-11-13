//
// Created by alexc on 11/9/2022.
//

#ifndef GLFW_TEST_VERTEXARRAY_H
#define GLFW_TEST_VERTEXARRAY_H
#include <vector>

class VertexArray {
    unsigned int VAO; //Id of the vertex array object, which represents the structure of the data in the vertex array
    unsigned int VBO; //Id of the vertex buffer object, which stores vertex locations
    unsigned int EBO; //Id of the element buffer object, which stores triangle data
    int numVertices;
    int triangleDataLen;
    int vertexLen;
    std::size_t currentVarOffset;

public:
    VertexArray(const std::vector<float> &vertices, int vertexLen, const std::vector<unsigned int> &triangleData);
    void bind() const;
    int getNumVertices() const;
    int getTriangleDataLen() const;
    VertexArray* vertexAttrib(int n, int size);
};


#endif //GLFW_TEST_VERTEXARRAY_H
