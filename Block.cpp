//
// Created by alexc on 11/26/2022.
//

#include "Block.h"

Block::Block(const char *name, short id, VertexArray vertexArray, Texture texture, glm::vec3 position) :
    ScreenObject(vertexArray, texture, position), blockName(name), blockId(id) {};

const char *Block::getName() {
    return blockName;
}

short Block::getId() {
    return blockId;
}


std::vector<std::unique_ptr<Block>> Block::blockTypes;

std::unique_ptr<Block> Block::newBlock(short id, glm::vec3 coords){
    if(id >= blockTypes.size() || blockTypes[id] == nullptr) return nullptr;
    return blockTypes[id]->clone(coords);
}