//
// Created by alexc on 11/13/2022.
//

#ifndef GLFW_TEST_CUBE_H
#define GLFW_TEST_CUBE_H
#include "ScreenObject.h"
#include <optional>

class Cube : public ScreenObject{
    static std::optional<VertexArray> vertexArr;
    //Initializes cubeEBO if it has not been initialized
    //Then returns cubeEBO
    static VertexArray getCubeVertexArr();

public:
    Cube(Texture texture, float scale, glm::vec3 position);
};


#endif //GLFW_TEST_CUBE_H
