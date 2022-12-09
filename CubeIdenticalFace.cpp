//
// Created by alexc on 11/13/2022.
//

#include "CubeIdenticalFace.h"
#include <vector>

std::vector<float> cube_ident_face_vertices{
        //x,y,z,tx,ty
        //front face
        -.5,-.5, .5,0,0,
        -.5, .5, .5,0,1,
        .5, .5, .5,1,1,
        .5,-.5, .5,1,0,

        //back face
        -.5,-.5, -.5,0,0,
        -.5, .5, -.5,0,1,
        .5,  .5, -.5,1,1,
        .5,-.5, -.5,1,0,

        //top face
        -.5, .5, .5,0,0,
        -.5, .5,-.5,0,1,
        .5, .5,-.5,1,1,
        .5, .5, .5,1,0,

        //bottom face
        -.5,-.5, .5,0,0,
        -.5,-.5,-.5,0,1,
        .5,-.5,-.5,1,1,
        .5,-.5, .5,1,0,

        //left face
        -.5,-.5,-.5,0,0,
        -.5, .5,-.5,0,1,
        -.5, .5, .5,1,1,
        -.5,-.5, .5,1,0,



        //right face
        .5,-.5,-.5,0,0,
        .5, .5,-.5,0,1,
        .5, .5, .5,1,1,
        .5,-.5, .5,1,0
};

std::vector<unsigned int> cube_ident_face_triangles{
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

std::optional<VertexArray> CubeIdenticalFace::vertexArr;

//If vertexArray has not been initialized, intialize it
//Then returns the value of vertexArray
VertexArray CubeIdenticalFace::getCubeVertexArr(){
    if(vertexArr == std::nullopt){
        vertexArr = VertexArray(cube_ident_face_vertices, 5, cube_ident_face_triangles);
        //Vertex attributes: 3 floats for rgb color, 2 floats for texture pos
        vertexArr->vertexAttrib(0,3)->vertexAttrib(1,2);
    }
    return *vertexArr;
}



//Creates a new cube object
//Initializes cubeEBO if it has not been initialized.
CubeIdenticalFace::CubeIdenticalFace(const char* name, int id, Texture texture, glm::vec3 position) : Block(name, id, getCubeVertexArr(), texture, texture, position){};

std::unique_ptr<Block> CubeIdenticalFace::clone(glm::vec3 position){
    return std::make_unique<CubeIdenticalFace>(CubeIdenticalFace(getName(), getId(), getTexture(), position));
}

void CubeIdenticalFace::initCubes(){
    blockTypes.push_back(nullptr);
    Texture stone("../textures/stone.png",{});
    blockTypes.push_back(std::make_unique<CubeIdenticalFace>(CubeIdenticalFace("Stone", 1, stone, glm::vec3(0, 0, 0))));
    Texture granite("../textures/granite.png",{});
    blockTypes.push_back(std::make_unique<CubeIdenticalFace>(CubeIdenticalFace("Granite", 2, granite, glm::vec3(0, 0, 0))));
    Texture calcite("../textures/diorite.png", {});
    blockTypes.push_back(std::make_unique<CubeIdenticalFace>(CubeIdenticalFace("Diorite", 3, calcite, glm::vec3(0, 0, 0))));
    Texture glass("../textures/glass.png",{});
    blockTypes.push_back(std::make_unique<CubeIdenticalFace>(CubeIdenticalFace("Glass", 4, glass,glm::vec3(0,0,0))));

}