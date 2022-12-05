//
// Created by alexc on 11/13/2022.
//

#ifndef GLFW_TEST_CUBE_H
#define GLFW_TEST_CUBE_H
#include "Block.h"
#include <optional>

class Cube : public Block{
    static std::optional<VertexArray> vertexArr;
    //Initializes cubeEBO if it has not been initialized
    //Then returns cubeEBO
    static VertexArray getCubeVertexArr();

public:
    Cube(const char* name, int id, Texture texture, glm::vec3 position);
    std::unique_ptr<Block> clone(glm::vec3 position) override;

    static void initCubes();
};


#endif //GLFW_TEST_CUBE_H
