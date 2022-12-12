//
// Created by alexc on 11/26/2022.
//

#ifndef GLFW_TEST_BLOCK_H
#define GLFW_TEST_BLOCK_H

#include <iostream>
#include <memory>
#include "ScreenObject.h"

//Represents a block-- any object that can be placed within the world
class Block : public ScreenObject{
    //A name for the type of block. Currently unused but could be useful in UI
    const char* blockName;
    //A flat 2d version of the blocks texture. On a cube-shaped block this is generally the front face of the cube
    //used in the menu that allows users to pick blocks
    Texture flatTexture;
    //The block's type's position in the blockTypes vector. Blocks which share a blockId are the same type and are the same
    //except for their position. It is used to represent the block in the save file
    short blockId;
public:
    Block(const char* name, short id, VertexArray vertexArray, Texture texture, Texture flatTexture, glm::vec3 position);

    virtual std::unique_ptr<Block> clone(glm::vec3 position)=0;
    const char* getName();
    short getId();
    Texture getFlatTexture();
    //Stores all the types of blocks. Blocks from this vector are copied to create new blocks to insert into the world
    //A block type's index in this vector is its blockId. The first element should be nullptr so that blockId zero is
    //an empty space.
    static std::vector<std::unique_ptr<Block >> blockTypes;
    //Creates a pointer to a new block of a type given the block type's id and a position
    static std::unique_ptr<Block> newBlock(short id, glm::vec3 coords);
};

#endif //GLFW_TEST_BLOCK_H
