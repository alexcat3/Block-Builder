//
// Created by alexc on 11/13/2022.
//

#include "ThreeDVec.h"
using std::vector;
template <typename T> ThreeDVec<T>::ThreeDVec(glm::vec3 dimensions){
    this->dimensions = dimensions;
    vec = vector<vector<vector<T>>>(dimensions.x, vector<vector<T>>(dimensions.y, vector<T>(dimensions.z)));
}

template <typename T> ThreeDVec<T>::ThreeDVec(int x, int y, int z) : ThreeDVec(glm::vec3(x,y,z)) {}

template <typename T> glm::vec3 &ThreeDVec<T>::getDimensions() { return dimensions; }

template <typename T> T& ThreeDVec<T>::at(int x, int y, int z) {
    return vec.at(x).at(y).at(z);
}

template <typename T> T& ThreeDVec<T>::at(glm::vec3 pos){
    return at(pos.x, pos.y, pos.z);
}