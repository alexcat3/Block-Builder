//
// Created by alexc on 11/10/2022.
//

#ifndef GLFW_TEST_TEXTURE_H
#define GLFW_TEST_TEXTURE_H
#include <iostream>
#include <glad/glad.h>

struct TextureOptions{
    int WRAP_S = GL_REPEAT;
    int WRAP_T = GL_REPEAT;
    int MIN_FILTER = GL_NEAREST;
    int MAG_FILTER = GL_NEAREST;
};
class Texture {
    unsigned int textureId;
public:
    Texture(std::string filename, struct TextureOptions options);
    void bind();
};


#endif //GLFW_TEST_TEXTURE_H
