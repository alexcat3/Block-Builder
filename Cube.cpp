//
// Created by alexc on 11/13/2022.
//

#include "Cube.h"
#include <vector>

std::vector<float> cube_vertices{
        //x,y,z,tx,ty
        //front face
        -1,-1, 1,0,0,
        -1, 1, 1,0,1,
        1, 1, 1,1,1,
        1,-1, 1,1,0,

        //back face
        -1,-1, -1,0,0,
        -1, 1, -1,0,1,
        1, 1, -1,1,1,
        1,-1, -1,1,0,

        //top face
        -1, 1, 1,0,0,
        -1, 1,-1,0,1,
        1, 1,-1,1,1,
        1, 1, 1,1,0,

        //bottom face
        -1,-1, 1,0,0,
        -1,-1,-1,0,1,
        1,-1,-1,1,1,
        1,-1, 1,1,0,

        //left face
        -1,-1,-1,0,0,
        -1, 1,-1,0,1,
        -1, 1, 1,1,1,
        -1,-1, 1,1,0,



        //right face
        1,-1,-1,0,0,
        1, 1,-1,0,1,
        1, 1, 1,1,1,
        1,-1, 1,1,0
};

std::vector<unsigned int> cube_triangles{
        //Front face
        0,1,2,
        2,3,0,
        //Back face
        4,5,6,
        6,7,4,
        //Top face
        8,9,10,
        10,11,8,
        //Bottom face
        12,13,14,
        14,15,12,
        //Left face
        16,17,18,
        18,19,16,
        //Right face
        20,21,22,
        22,23,20
};

std::optional<ElementBufferObject> Cube::cubeEBO;

//If cubeEBO has not been initialized, intialize it
//Then returns the value of cubeEBO
ElementBufferObject Cube::getCubeEBO(){
    if(cubeEBO == std::nullopt){
        cubeEBO = ElementBufferObject(cube_vertices, 5, cube_triangles);
        //Vertex attributes: 3 floats for rgb color, 2 floats for texture pos
        cubeEBO->vertexAttrib(0,3)->vertexAttrib(1,2);
    }
    return *cubeEBO;
}


//Creates a new cube object
//Initializes cubeEBO if it has not been initialized.
Cube::Cube(Texture texture, float scale, glm::vec3 position) : ScreenObject(getCubeEBO(), texture, scale, position){};