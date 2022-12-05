//
// Created by alexc on 12/1/2022.
//

#include "World.h"
#include "glm/gtx/string_cast.hpp"
#include <fstream>

 World::World(short width, short height, short length): world(width, height, length){
    std::cout<<world.at(0,0,0)->getId();
}

 World::World(std::string filename) : world(1,1,1){

    std::ifstream saveFile(filename, std::ios::binary);
    //If the save file exists load the world data from it
    if(saveFile) {
        short width, height, length;
        //First 3 shorts are dimensions of world
        saveFile.read((char*)&width, sizeof(short));
        saveFile.read((char*)&height, sizeof(short));
        saveFile.read((char*)&length, sizeof(short));
        //Then read in array of blocks
        world = ThreeDVec<std::unique_ptr<Block>>(width, height, length);
        for(int x=0; x<width; x++) {
            for (int y = 0; y < height; y++) {
                for (int z = 0; z < length; z++) {
                    short blockId;
                    saveFile.read((char*)&blockId, sizeof(short));
                    world.at(x,y,z) = Block::newBlock(blockId, glm::vec3(x,y,z));
                }
            }
        }
    }else{
        world = ThreeDVec<std::unique_ptr<Block>>(DEFAULT_WIDTH,DEFAULT_HEIGHT,DEFAULT_LENGTH);
        createStoneFloor();
    }
 }

 void World::createStoneFloor(){
     for(short x=0; x<world.getDimensions().x; x++) {
         for(short z=0; z<world.getDimensions().z; z++) {
             world.at(x,0,z) = Block::newBlock(1,glm::vec3(x,0,z));
         }
     }
}


void World::saveToFile(std::string filename) {
     std::ofstream saveFile(filename, std::ios::binary);
     //File begins with world dimensions as shorts
     short xDim = world.getDimensions().x;
     short yDim = world.getDimensions().y;
     short zDim = world.getDimensions().z;
     saveFile.write((char*)&xDim, sizeof(short));
     saveFile.write((char*)&yDim, sizeof(short));
     saveFile.write((char*)&zDim, sizeof(short));

     for(int i=0; i<world.getDimensions().x; i++){
         for(int j=0; j<world.getDimensions().y; j++){
             for(int k=0; k<world.getDimensions().z; k++){
                 if(world.at(i,j,k) == nullptr){
                     saveFile.write("\0\0",sizeof(short));
                 }else{
                     short id = world.at(i,j,k)->getId();
                     saveFile.write((char*)&id,sizeof(short));
                 }
             }
         }
     }
     saveFile.close();
 }

 std::unique_ptr<Block>& World::at(short x, short y, short z){
     return world.at(x,y,z);
 }

 std::unique_ptr<Block>& World::at(glm::vec3 pos){
     return world.at(pos);
 }

 void World::draw() {
    for(int x=0; x<world.getDimensions().x; x++){
        for(int y=0; y<world.getDimensions().y; y++){
            for(int z=0; z<world.getDimensions().z; z++){
                if(world.at(x,y,z) != nullptr) {
                    world.at(x, y, z)->draw();
                }
            }
        }
    }
 }

 glm::vec3 floor(glm::vec3 v){
    return glm::vec3(floor(v.x),floor(v.y), floor(v.z));
}

std::optional<CameraTarget> World::findCameraTarget(Camera &camera){
    glm::vec3 pos = camera.getPos();
    int dist = 12;
    float increment = .125;
    for(float i=0; i<dist; i+=increment){
        if(world.inBounds(pos) && world.at(pos) != nullptr){

            return CameraTarget({addPos:floor(pos-camera.getDirection()*increment), deletePos:floor(pos)});
        }
        pos += camera.getDirection() * increment;
    }
    return std::nullopt;
}

bool World::inBounds(glm::vec3 pos) {
    return world.inBounds(pos);
}

 glm::vec3 World::getDimensions(){
     return world.getDimensions();
 }