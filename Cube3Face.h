//
// Created by alexc on 12/5/2022.
//

#ifndef GLFW_TEST_CUBE3FACE_H
#define GLFW_TEST_CUBE3FACE_H
#include <optional>
#include "VertexArray.h"
#include "Block.h"

class Cube3Face : public Block{
        static std::optional<VertexArray> vertexArr;
        //Initializes cubeEBO if it has not been initialized
        //Then returns cubeEBO
        static VertexArray getCubeVertexArr();

    public:
        Cube3Face(const char* name, int id, Texture texture, Texture flatTexture, glm::vec3 position);
        std::unique_ptr<Block> clone(glm::vec3 position) override;

        static void initCubes();
};



#endif //GLFW_TEST_CUBE3FACE_H
