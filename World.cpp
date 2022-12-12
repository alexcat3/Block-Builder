//
// Created by alexc on 12/1/2022.
//

#include "World.h"
#include "glm/gtx/string_cast.hpp"
#include <fstream>

 World::World(short width, short height, short length): worldVec(width, height, length){
    createStoneFloor();
}

 World::World(std::string filename) : worldVec(1,1,1){
    std::ifstream saveFile(filename, std::ios::binary);
    //If the save file exists load the world data from it
    if(saveFile) {
        short width, height, length;
        //First 3 shorts are dimensions of world
        saveFile.read((char*)&width, sizeof(short));
        saveFile.read((char*)&height, sizeof(short));
        saveFile.read((char*)&length, sizeof(short));
        //Then read in array of block ids
        worldVec = ThreeDVec<std::unique_ptr<Block>>(width, height, length);
        for(int x=0; x<width; x++) {
            for (int y = 0; y < height; y++) {
                for (int z = 0; z < length; z++) {
                    short blockId;
                    saveFile.read((char*)&blockId, sizeof(short));
                    worldVec.at(x,y,z) = Block::newBlock(blockId, glm::vec3(x,y,z));
                }
            }
        }
    }else{
        worldVec = ThreeDVec<std::unique_ptr<Block>>(DEFAULT_WIDTH,DEFAULT_HEIGHT,DEFAULT_LENGTH);
        createStoneFloor();
    }
 }

 void World::createStoneFloor(){
     for(short x=0; x<worldVec.getDimensions().x; x++) {
         for(short z=0; z<worldVec.getDimensions().z; z++) {
             worldVec.at(x,0,z) = Block::newBlock(1,glm::vec3(x,0,z));
         }
     }
}


void World::saveToFile(std::string filename) {
     std::ofstream saveFile(filename, std::ios::binary);
     //File begins with world dimensions as shorts
     short xDim = worldVec.getDimensions().x;
     short yDim = worldVec.getDimensions().y;
     short zDim = worldVec.getDimensions().z;
     saveFile.write((char*)&xDim, sizeof(short));
     saveFile.write((char*)&yDim, sizeof(short));
     saveFile.write((char*)&zDim, sizeof(short));

     //Now write all of the blockIds to the file as shorts
     for(int i=0; i<worldVec.getDimensions().x; i++){
         for(int j=0; j<worldVec.getDimensions().y; j++){
             for(int k=0; k<worldVec.getDimensions().z; k++){
                 if(worldVec.at(i,j,k) == nullptr){
                     saveFile.write("\0\0",sizeof(short));
                 }else{
                     short id = worldVec.at(i,j,k)->getId();
                     saveFile.write((char*)&id,sizeof(short));
                 }
             }
         }
     }
     saveFile.close();
 }

 std::unique_ptr<Block>& World::at(short x, short y, short z){
     return worldVec.at(x,y,z);
 }

 std::unique_ptr<Block>& World::at(glm::vec3 pos){
     return worldVec.at(pos);
 }

 void World::draw(glm::vec3 cameraPos) {
    //In order for transparency to work, we must draw all of the blocks behind a transparent block from the camera's
    //perspective before we draw that block. A block can only be seen as behind another block if it has a greater taxicab
    //distance (change in x + change in y + change in z) from the camera than that other block. Therefore, we draw blocks
    //in order of greatest to least taxicab distance from the camera
    for(int taxiCabDist = worldVec.getDimensions().x+worldVec.getDimensions().y + worldVec.getDimensions().z; taxiCabDist >0; taxiCabDist--){
        //Cycle through all possible dx and dy values from the camera's postiton, taking into account that x and y cant exceed the bounds of the world
        for(int dx = floor(-cameraPos.x); floor(dx + cameraPos.x) < worldVec.getDimensions().x; dx++){
            for(int dy=floor(-cameraPos.y); floor(dy + cameraPos.y) < worldVec.getDimensions().y; dy++){
                //Two possible dz values at the given taxicab distance, positive and negative
                int dz = taxiCabDist - abs(dx) - abs(dy);
                //If either (x+dz y+dy z+dz) or (x+dx y+dy z-dz) is in the bounds of the world, draw the block at that position
                glm::vec3 drawPos1 = glm::vec3(dx+cameraPos.x, dy+cameraPos.y, dz+cameraPos.z);
                glm::vec3 drawPos2 = glm::vec3(dx+cameraPos.x, dy+cameraPos.y, -dz+cameraPos.z);
                if(worldVec.inBounds(drawPos1) && worldVec.at(drawPos1) != nullptr){
                    worldVec.at(drawPos1)->draw();
                }
                if(worldVec.inBounds(drawPos2) && worldVec.at(drawPos2) != nullptr){
                    worldVec.at(drawPos2)->draw();
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
    int dist = 12; //Max distance between the target and the camera
    float increment = .125; //Distance to step forward when looking for a target block
    //Start at the camera's position, and keep moving forward in the direction the camera is pointing until a target
    //block is found or the maximum distance is exceeded
    for(float i=0; i<dist; i+=increment){
        if(worldVec.inBounds(pos) && worldVec.at(pos) != nullptr){
            return CameraTarget({addPos:floor(pos-camera.getDirection()*increment), deletePos:floor(pos)});
        }
        pos += camera.getDirection() * increment;
    }
    return std::nullopt;
}

bool World::inBounds(glm::vec3 pos) {
    return worldVec.inBounds(pos);
}

 glm::vec3 World::getDimensions(){
     return worldVec.getDimensions();
 }