//
// Created by alexc on 11/13/2022.
//

#ifndef GLFW_TEST_THREEDVEC_H
#define GLFW_TEST_THREEDVEC_H
#include <vector>
#include "../lib/glm/glm.hpp"
//A 3 dimensional array of a fixed size
//can be accessed using a vector of coordinates
template <typename T> class ThreeDVec {
    glm::vec3 dimensions;
    std::vector<std::vector<std::vector<T>>> vec;
public:
    explicit ThreeDVec(glm::vec3 dimensions);
    ThreeDVec(int x, int y, int z);

    glm::vec3 getDimensions();

    //Returns the value at the given position
    //In the vec3 version, coordinates are rounded down to integers
    T &at(glm::vec3 pos);
    T &at(int x, int y, int z);
    //Determines if, when the coordinates are rounded down to integers, the position is within the bounds of the vector
    bool inBounds(glm::vec3 pos);
};


#endif //GLFW_TEST_THREEDVEC_H
