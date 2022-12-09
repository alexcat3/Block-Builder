//
// Created by alexc on 11/26/2022.
//

#ifndef GLFW_TEST_BLOCK_H
#define GLFW_TEST_BLOCK_H

#include <iostream>
#include <memory>
#include "ScreenObject.h"

class Block : public ScreenObject{
    const char* blockName;
    Texture flatTexture;
    short blockId;
public:
    Block(const char* name, short id, VertexArray vertexArray, Texture texture, Texture flatTexture, glm::vec3 position);

    virtual std::unique_ptr<Block> clone(glm::vec3 position)=0;
    const char* getName();
    short getId();
    Texture getFlatTexture();
    static std::vector<std::unique_ptr<Block >> blockTypes;
    static std::unique_ptr<Block> newBlock(short id, glm::vec3 coords);
};

#endif //GLFW_TEST_BLOCK_H
