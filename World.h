//
// Created by alexc on 12/1/2022.
//

#ifndef GLFW_TEST_WORLD_H
#define GLFW_TEST_WORLD_H
#include "ThreeDVec.h"
#include "ThreeDVec.cpp"
#include "Block.h"
#include "Camera.h"

struct CameraTarget{
    glm::vec3 addPos;
    glm::vec3 deletePos;
};

class World {
    ThreeDVec<std::unique_ptr<Block>> world;
    void createStoneFloor();
    std::optional<glm::vec3> cameraTarget;

public:
    explicit World(short width, short height, short length);
    explicit World(std::string filename);

    void draw(glm::vec3 cameraPos);
    void saveToFile(std::string filename);
    std::optional<CameraTarget> findCameraTarget(Camera &camera);
    std::unique_ptr<Block> &at(short x, short y, short z);
    std::unique_ptr<Block> &at(glm::vec3 pos);
    glm::vec3 getDimensions();
    bool inBounds(glm::vec3 pos);

    const int DEFAULT_HEIGHT = 16;
    const int DEFAULT_WIDTH = 64;
    const int DEFAULT_LENGTH = 64;
};


#endif //GLFW_TEST_WORLD_H
