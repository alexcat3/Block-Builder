//
// Created by alexc on 12/5/2022.
//

#include "Cube3Face.h"
//
// Created by alexc on 11/13/2022.
//

#include <vector>

std::vector<float> cube3face_vertices{
        //x,y,z,tx,ty
        //front face
        -.5,-.5, .5,0,1.0f/3,
        -.5, .5, .5,0,2.0f/3,
        .5, .5, .5, 1,2.0f/3,
        .5,-.5, .5, 1,1.0f/3,

        //back face
        -.5,-.5, -.5,0,1.0f/3,
        -.5, .5, -.5,0,2.0f/3,
        .5,  .5, -.5,1,2.0f/3,
        .5,-.5, -.5, 1,1.0f/3,

        //top face
        -.5, .5, .5, 0,0,
        -.5, .5,-.5, 0,1.0f/3,
         .5, .5,-.5, 1, 1.0f/3,
         .5, .5, .5, 1, 0,

        //bottom face
        -.5,-.5, .5, 0, 1,
        -.5,-.5,-.5, 0, 2.0f/3,
         .5,-.5,-.5, 1, 2.0f/3,
         .5,-.5, .5, 1, 1,

        //left face
        -.5,-.5,-.5, 0,1.0f/3,
        -.5, .5,-.5, 0,2.0f/3,
        -.5, .5, .5, 1,2.0f/3,
        -.5,-.5, .5, 1,1.0f/3,



        //right face
        .5,-.5,-.5, 0,1.0f/3,
        .5, .5,-.5, 0,2.0f/3,
        .5, .5, .5, 1,2.0f/3,
        .5,-.5, .5, 1,1.0f/3
};

std::vector<unsigned int> cube3face_triangles{
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

std::optional<VertexArray> Cube3Face::vertexArr;

//If vertexArray has not been initialized, intialize it
//Then returns the value of vertexArray
VertexArray Cube3Face::getCubeVertexArr(){
    if(vertexArr == std::nullopt){
        vertexArr = VertexArray(cube3face_vertices, 5, cube3face_triangles);
        //Vertex attributes: 3 floats for rgb color, 2 floats for texture pos
        vertexArr->vertexAttrib(0,3)->vertexAttrib(1,2);
    }
    return *vertexArr;
}



//Creates a new cube object
//Initializes cubeEBO if it has not been initialized.
Cube3Face::Cube3Face(const char* name, int id, Texture texture, Texture flatTexture, glm::vec3 position) : Block(name, id, getCubeVertexArr(), texture, flatTexture, position){};

std::unique_ptr<Block> Cube3Face::clone(glm::vec3 position){
    return std::make_unique<Cube3Face>(Cube3Face(getName(), getId(), getTexture(), getFlatTexture(), position));
}

void Cube3Face::initCubes(){
    Texture sandstone("../textures/sandstone_top.png","../textures/sandstone_side.png","../textures/sandstone_bottom.png", {});
    Texture sandstoneFlat("../textures/sandstone_side.png", {});
    //blockTypes.push_back(std::make_unique<Cube3Face>(Cube3Face("Sandstone", 5, sandstone, sandstoneFlat, glm::vec3(0, 0, 0))));

}