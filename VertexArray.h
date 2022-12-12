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
    int numVertices; //Number of vertices in the vertex array
    int triangleDataLen; //Number of floats in the triangle data
    int vertexLen; //Number of floats per vertex in the vertex array
    std::size_t currentVarOffset; //The offset of the last vertex attribute assigned

public:
    VertexArray(const std::vector<float> &vertices, int vertexLen, const std::vector<unsigned int> &triangleData);
    //Use this vertex array to draw the next object
    void bind() const;
    int getNumVertices() const;
    int getTriangleDataLen() const;
    //The nth vertex attribute will be a vector of the next size floats in the vertex
    VertexArray* vertexAttrib(int n, int size);
};


#endif //GLFW_TEST_VERTEXARRAY_H
