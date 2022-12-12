//
// Created by alexc on 12/11/2022.
//
#include <iostream>
#include "Camera.h"
#include "Block.h"
#include "CubeIdenticalFace.h"
#include "World.h"
#include "InitWindow.cpp"
#include "glm/gtx/string_cast.hpp"

//Test if two vectors are approximately equal
//Floating point rounding errors may mean that two vectors that should be equal are not exactly equal
bool approxEqu(glm::vec3 v1, glm::vec3 v2){
    return glm::all(glm::epsilonEqual(v1, v1, glm::vec3(.01)));
}
bool approxEqu(glm::vec4 v1, glm::vec4 v2){
    return glm::all(glm::epsilonEqual(v1, v2, glm::vec4(.01)));
}

int main(){
    //Many of the methods/classes used in this program cannot be easily tested as they only output to the screen
    //This test suite attempts to test every part of the program that can be tested in a straight forward way

    //The classes assume OpenGL is initialized and a window exists, so we initialize it and create a window
    GLFWwindow* window = initWindow(800,600);

    //Initialize cubes w/ identical faces
    CubeIdenticalFace::initCubes();

    //*** Test the camera class
    //The projection matrix is generated entirely by the glm library so we will only test the view matrix
    std::cout<<"Testing Camera.cpp"<<std::endl;
    glm::vec3 pos(-3,4,7);
    Camera cam(pos, 45, 4.0f/3, 0.1, 12, window);

    //The initial camera direction should be along the negative z axis, facing "inward", so that world coordinates match
    //view coordinates when the camera is at the origin
    if(!approxEqu(cam.getDirection(), glm::vec3(0,0,-1))){
        std::cout<<"Error: initial direction should be (0,0,-1), not "<<glm::to_string(cam.getDirection())<<std::endl;
    }
    //The view matrix shoud map the camera's position to (0,0,0)
    glm::vec4 camPosMap = cam.getViewMatrix()*glm::vec4(pos,1);
    if(!approxEqu(camPosMap, glm::vec4(0, 0, 0, 1))){
        std::cout<<"Error: Camera view matrix should map camera's position to the origin, not "<<glm::to_string(camPosMap)<<"!"<<std::endl;
    }
    //Before the camera has been rotated, the view matrix should map the camera's position + a random offset to that offset
    glm::vec3 offset( rand() % 32, rand()%32, rand()%32);
    glm::vec4 offsetMap = cam.getViewMatrix() * glm::vec4(pos+offset,1);
    if(!approxEqu(offsetMap, offset)){
        std::cout<<"Error: Camera view matrix does not subtract the camera's position from the coordinates"<<std::endl;
        std::cout<<"pos + "<<glm::to_string(offset)<<" should map to "<<glm::to_string(offset)<<"not "<<glm::to_string(offsetMap)<<std::endl;
    }

    //Rotate the camera by 45 degrees
    cam.rotateRad(M_PI/4);
    //After the camera is rotated, the camera's position should still map to (0,0,0)
    camPosMap = cam.getViewMatrix() * glm::vec4(pos,1);
    if(!approxEqu(camPosMap, glm::vec4(0,0,0,1))){
        std::cout<<"Error: Rotation matrix moves the origin!"<<std::endl;
    }
    //When the camera has been rotated but not tilted, the matrix should not alter y values
    if(!approxEqu(cam.getViewMatrix()*glm::vec4((pos+glm::vec3(0,1,0)),1), glm::vec4(0,1,0,1))){
        std::cout<<"Error: Rotation matrix affects the y axis!"<<std::endl;
    }
    //Check that a certain point is mapped correctly
    glm::vec4 testMap1 = cam.getViewMatrix()*glm::vec4(pos+glm::vec3(-1,0,0),1);
    if(!approxEqu(testMap1,glm::vec4(-sqrt(2)/2, 0, -sqrt(2)/2, 1))){
        std::cout<<"Error: incorrect rotation matrix!"<<std::endl;
        std::cout<<"When yaw = pi/4, -1,0,0 should map to sqrt(2)/2, 0, -sqrt(2)/2, not "<<glm::to_string(testMap1)<<std::endl;
    }
    //Check that the camera is pointing in the right direction
    if(!approxEqu(cam.getDirection(), glm::vec3(sqrt(2)/2, 0, sqrt(2)/2))){
        std::cout<<"Error: incorrect rotation getDirection() result!"<<std::endl;
    }
    //Undo the rotation
    cam.rotateRad(-M_PI/4);

    //Tilt the camera by 45 degrees
    cam.tiltRad(M_PI/4);
    camPosMap = cam.getViewMatrix() * glm::vec4(pos,1);
    //Check that the camera's position still maps to  (0,0,0)
    if(!approxEqu(camPosMap, glm::vec4(0,0,0,1))){
        std::cout<<"Error: Tilting moves the origin!"<<std::endl;
        std::cout<<"Camera position should map to (0,0,0), not "<<glm::to_string(camPosMap);
    }
    //When the camera has been tilted but not rotated, the x coordinates should not be affected
    if(!approxEqu(cam.getViewMatrix()*glm::vec4((pos)+glm::vec3(1,0,0), 1), glm::vec4(1,0,0,1))){
        std::cout<<"Error: Tilting w/o rotation affects the x axis!"<<std::endl;
    }
    //Check that a certain point is mapped to the correct location
    glm::vec4 testMap3 = cam.getViewMatrix()*glm::vec4(pos+glm::vec3(0,1,0),1);
    if(!approxEqu(testMap3, glm::vec4(0,sqrt(2)/2,-sqrt(2)/2,1))){
        std::cout<<"Error: Incorrect tilting matrix!"<<std::endl;
    }
    //Check that the camera is pointed in the right direction
    if(!approxEqu(cam.getDirection(), glm::vec3(0, sqrt(2)/2, -sqrt(2)/2))){
        std::cout<<"Error: Incorrect tilting camera direction!"<<std::endl;
    }

    //Check that camera cannot be tilted more than 90 degrees up
    cam.tiltRad(M_PI/2);
    if(cam.getPitchRad() > M_PI){
        std::cout<<"Error: Camera should not be tiltable past 90 degrees up!"<<std::endl;
    }
    cam.tiltRad((-3*M_PI/2));
    if(cam.getPitchRad() < 0){
        std::cout<<"Error: Camera should not be tiltable past 90 degrees down!"<<std::endl;
    }

    //*** Test world class
    //as the world class uses the ThreeDVec class, this code acts as a test of ThreeDVec
    std::cout<<"\n\nTesting world class"<<std::endl;
    World w1(10,7,9);
    //Inbounds method should return true if three coords are in bounds
    //A coordinate is in bounds if it is >= 0 and less than the world's dimension
    if(w1.inBounds(glm::vec3(10, 1, 1)) || w1.inBounds(glm::vec3(1,7,1)) || w1.inBounds(glm::vec3(1,1,9))){
        std::cout<<"Error: if a coordinate is greater than one of the worlds dimensions, it should not be in bounds"<<std::endl;
    }
    if(!w1.inBounds(glm::vec3(0,0,0))){
        std::cout<<"Error: 0 coordinates should be in bounds"<<std::endl;
    }
    if(w1.inBounds(glm::vec3(-.1, 0, 0)) || w1.inBounds(glm::vec3(0,-.1,0)) || w1.inBounds(glm::vec3(0,0,-.1))){
        std::cout<<"Error: negative decimal coordinates should not be in bounds"<<std::endl;
    }
    if(w1.getDimensions() != glm::vec3(10,7,9)){
        std::cout<<"Error: getDimensions() does not work"<<std::endl;
    }

    //The world should have a stone floor
    int stoneBlockId = 1;
    for(int x=0; x<w1.getDimensions().x; x++){
        for(int z=0; z<w1.getDimensions().y; z++){
            if(w1.at(x,0,z) == nullptr || w1.at(x,0,z)->getId() != stoneBlockId){
                std::cout<<"Part of stone floor missing at "<<x<<", 0, "<<z<<std::endl;
            }
        }
    }
    //Other than the floor, the rest of the world should be empty
    for(int x=0; x<w1.getDimensions().x; x++){
        for(int y=1; y<w1.getDimensions().y; y++){
            for(int z=0; z<w1.getDimensions().z; z++){
                if(w1.at(x,y,z)!=nullptr){
                    std::cout<<"Spurious block in world at "<<x<<", "<<y<<", "<<z<<"!\n";
                }
            }
        }
    }

    //Add a block to the world
    //At function should round down coordinates
    int cobblestoneId = 2;
    w1.at(glm::vec3(3.4,5.1,2.2)) = Block::newBlock(cobblestoneId, glm::vec3(3,5,2));
    if(w1.at(glm::vec3(3,5,2)) == nullptr || w1.at(3,5,2)->getId() != cobblestoneId){
        std::cout<<"Adding a block to the world failed!"<<std::endl;
    }

    //Save the world to a file and reload it
    w1.saveToFile("test.wld");
    World w2("test.wld");
    //The save file should have preserved the dimensions
    if(w1.getDimensions() != w2.getDimensions()){
        std::cout<<"Error: Dimensions not preserved in save file!"<<std::endl;
    }
    //Check that all blocks are the same in the saved version
    for(int x=0; x<w1.getDimensions().x; x++){
        for(int y=0; y<w1.getDimensions().y; y++){
            for(int z=0; z<w1.getDimensions().z; z++){
                if((w1.at(x,y,z) == nullptr) != (w2.at(x,y,z) == nullptr) || (w1.at(x,y,z)!= nullptr && w1.at(x,y,z)->getId() != w2.at(x,y,z)->getId())){
                    std::cout<<"Error: world saved incorrectly!"<<std::endl;
                }
            }
        }
    }

    //Test the features of the ScreenObject class using CubeIdenticalFace
    std::cout<<"Testing ScreenObject, Block and CubeIdenticalFace"<<std::endl;
    glm::vec3 blockPos(1,5,2);
    std::unique_ptr<Block> stoneBlock = Block::newBlock(stoneBlockId, blockPos);
    //The origin in the geometry data should be mapped to the block's position
    glm::vec4 originMapping = stoneBlock->getModel() * glm::vec4(0,0,0,1);
    if(!approxEqu(originMapping, glm::vec4(blockPos,1))){
        std::cout<<"Origin should be mapped to block position "<<glm::to_string(blockPos)<<", not "<<glm::to_string(originMapping)<<std::endl;
    }
    //When the block has not been rotated, non-origin set of coordinates should be mapped to those coordinates plus the block's position
    glm::vec3 coords = glm::vec3(4,2,1);
    glm::vec4 blockCoordsMapping = stoneBlock->getModel() * glm::vec4(coords,1);
    if(!approxEqu(blockCoordsMapping, glm::vec4(coords+blockPos,1))){
        std::cout<<"When a block has not been rotated, coords should be mapped to the blocks position plus those coordinates\n";
        std::cout<<glm::to_string(coords)<<" should be mapped to "<<glm::to_string(coords+blockPos)<<" not "<<glm::to_string(blockCoordsMapping);
    }
    //Rotating the block should not change the origin
    stoneBlock->rotateRad(M_PI/4, glm::vec3(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    originMapping = stoneBlock->getModel() * glm::vec4(0,0,0,1);
    if(!approxEqu(originMapping, blockPos)){
        std::cout<<"Rotating a block should not alter the origin\n";
        std::cout<<"The origin should be mapped to block position "<<glm::to_string(blockPos)<<", not "<<glm::to_string(originMapping)<<std::endl;
    }




}