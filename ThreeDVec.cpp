//
// Created by alexc on 11/13/2022.
//

#include "ThreeDVec.h"
using std::vector;
template <typename T> ThreeDVec<T>::ThreeDVec(glm::vec3 dimensions){
    this->dimensions = dimensions;
    vec = vector<vector<vector<T>>>(dimensions.x);
    for(int i=0; i<dimensions.x; i++){
        vec[i] = vector<vector<T>>(dimensions.y);
    }

    for(int i=0; i<dimensions.x; i++){
        for(int j=0; j<dimensions.y; j++){
            vec[i][j] = vector<T>(dimensions.z);
        }
    }
}

template <typename T> ThreeDVec<T>::ThreeDVec(int x, int y, int z) : ThreeDVec(glm::vec3(x,y,z)) {}

template <typename T> glm::vec3 ThreeDVec<T>::getDimensions()
    {
    return dimensions; }

template <typename T> T& ThreeDVec<T>::at(int x, int y, int z) {
    int q = vec.size();
    return vec.at(x).at(y).at(z);
}

template <typename T> T& ThreeDVec<T>::at(glm::vec3 pos){
    return at(floor(pos.x), floor(pos.y), floor(pos.z));
}

template <typename T> bool ThreeDVec<T>::inBounds(glm::vec3 pos) {
    return pos.x >= 0 && pos.x < dimensions.x && pos.y >= 0 && pos.y < dimensions.y && pos.z >= 0 && pos.z < dimensions.z;
}