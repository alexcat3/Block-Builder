//
// Created by alexc on 12/5/2022.
//

#ifndef GLFW_TEST_CUBE4FACE_H
#define GLFW_TEST_CUBE4FACE_H
#include <optional>
#include "VertexArray.h"
#include "Block.h"

//Represents a cube with 4 distinct faces-- one for the top, one for the front, one for the sides, and one for the bottom
//Faces are stacked vertically in the texture in that order
class Cube4Face : public Block{
        static std::optional<VertexArray> vertexArr;
        //Initializes cubeEBO if it has not been initialized
        //Then returns cubeEBO
        static VertexArray getCubeVertexArr();

    public:
        Cube4Face(const char* name, int id, Texture texture, Texture flatTexture, glm::vec3 position);
        std::unique_ptr<Block> clone(glm::vec3 position) override;

        //Initialize all 4 face cube block types and add them to the block type array
        static void initCubes();
};



#endif //GLFW_TEST_CUBE4FACE_H
