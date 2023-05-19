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
    //Vector where the blocks are stored
    ThreeDVec<std::unique_ptr<Block>> worldVec;
    //Fill all blocks where y=0 with stone to create a platform to build on
    void createStoneFloor();

public:
    //Create new empty world width given width, length, and height
    explicit World(short width, short height, short length);
    //If the file exists, load the world from the file. Otherwise, create an empty world with default dimensions
    explicit World(std::string filename);

    //Draw all blocks in the world to the screen
    void draw(glm::vec3 cameraPos);
    //Save the world to a file at given filename
    void saveToFile(std::string filename);
    //Find the block which the camera is looking at, and the empty space between it and the camera where a block can be added
    std::optional<CameraTarget> findCameraTarget(Camera &camera);
    //Get the block at the given position
    std::unique_ptr<Block> &at(short x, short y, short z);
    std::unique_ptr<Block> &at(glm::vec3 pos);
    //Get the dimensions of the world
    glm::vec3 getDimensions();
    //Returns true if, when the coordinates are rounded down, the position is within the bounds of the world.
    bool inBounds(glm::vec3 pos);

    //Default dimensions for a world
    const int DEFAULT_HEIGHT = 16;
    const int DEFAULT_WIDTH = 64;
    const int DEFAULT_LENGTH = 64;
};


#endif //GLFW_TEST_WORLD_H
