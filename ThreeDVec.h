//
// Created by alexc on 11/13/2022.
//

#ifndef GLFW_TEST_THREEDVEC_H
#define GLFW_TEST_THREEDVEC_H
#include <vector>
#include "glm/glm.hpp"

template <typename T> class ThreeDVec {
    glm::vec3 dimensions;
    std::vector<std::vector<std::vector<T>>> vec;
public:
    explicit ThreeDVec(glm::vec3 dimensions);
    ThreeDVec(int x, int y, int z);

    glm::vec3 getDimensions();

    T &at(glm::vec3 pos);
    T &at(int x, int y, int z);

    bool inBounds(glm::vec3 pos);
};


#endif //GLFW_TEST_THREEDVEC_H
