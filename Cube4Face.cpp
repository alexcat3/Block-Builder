//
// Created by alexc on 12/5/2022.
//

#include "Cube4Face.h"
//
// Created by alexc on 11/13/2022.
//

#include <vector>
//Vertex data for 4 face cube
std::vector<float> cube4face_vertices{
        //x,y,z,tx,ty
        //front face
        -.5,-.5, .5,0,.25,
        -.5, .5, .5,0,.5,
        .5, .5, .5, 1,.5,
        .5,-.5, .5, 1,.25,

        //back face
        -.5,-.5, -.5,0,.5,
        -.5, .5, -.5,0,.75,
        .5,  .5, -.5,1,.75,
        .5,-.5, -.5, 1,.5,

        //top face
        -.5, .5, .5, 0,0,
        -.5, .5,-.5, 0,.25,
         .5, .5,-.5, 1,.25,
         .5, .5, .5, 1, 0,

        //bottom face
        -.5,-.5, .5, 0, .75,
        -.5,-.5,-.5, 0, 1,
         .5,-.5,-.5, 1, 1,
         .5,-.5, .5, 1, .75,

        //left face
        -.5,-.5,-.5, 0,.5,
        -.5, .5,-.5, 0, .75,
        -.5, .5, .5, 1, .75,
        -.5,-.5, .5, 1, .5,



        //right face
        .5,-.5,-.5, 0,.5,
        .5, .5,-.5, 0,.75,
        .5, .5, .5, 1,.75,
        .5,-.5, .5, 1,.5
};

std::vector<unsigned int> cube4face_triangles{
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

std::optional<VertexArray> Cube4Face::vertexArr;

//If vertexArray has not been initialized, initialize it
//Then returns the value of vertexArray
VertexArray Cube4Face::getCubeVertexArr(){
    if(vertexArr == std::nullopt){
        vertexArr = VertexArray(cube4face_vertices, 5, cube4face_triangles);
        //Vertex attributes: 3 floats for rgb color, 2 floats for texture pos
        vertexArr->vertexAttrib(0,3)->vertexAttrib(1,2);
    }
    return *vertexArr;
}



//Creates a new cube object
//Initializes cubeEBO if it has not been initialized.
Cube4Face::Cube4Face(const char* name, int id, Texture texture, Texture flatTexture, glm::vec3 position) : Block(name, id, getCubeVertexArr(), texture, flatTexture, position){};

std::unique_ptr<Block> Cube4Face::clone(glm::vec3 position){
    return std::make_unique<Cube4Face>(Cube4Face(getName(), getId(), getTexture(), getFlatTexture(), position));
}

//Initialize all 4 face cube block types and add them to the blockTypes array
void Cube4Face::initCubes(){
    Texture sandstone("../textures/sandstone_top.png","../textures/sandstone_side.png","../textures/sandstone_side.png","../textures/sandstone_bottom.png", {});
    Texture sandstoneFlat("../textures/sandstone_side.png", {});
    blockTypes.push_back(std::make_unique<Cube4Face>(Cube4Face("Sandstone", blockTypes.size(), sandstone, sandstoneFlat, glm::vec3(0, 0, 0))));

    Texture craftingTable("../textures/crafting_table_top.png", "../textures/crafting_table_front.png", "../textures/crafting_table_side.png", "../textures/crafting_table_top.png", {});
    Texture craftingTableFlat("../textures/crafting_table_front.png", {});
    blockTypes.push_back(std::make_unique<Cube4Face>(Cube4Face("Crafting Table", blockTypes.size(), craftingTable, craftingTableFlat, glm::vec3(0,0,0))));

    Texture furnace("../textures/furnace_top.png", "../textures/furnace_front.png", "../textures/furnace_side.png", "../textures/furnace_top.png", {});
    Texture furnaceFlat("../textures/furnace_front.png", {});
    blockTypes.push_back(std::make_unique<Cube4Face>(Cube4Face("Furnace", blockTypes.size(), furnace, furnaceFlat, glm::vec3(0,0,0))));
}