//
// Created by alexc on 11/10/2022.
//

#ifndef GLFW_TEST_TEXTURE_H
#define GLFW_TEST_TEXTURE_H
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
struct TextureOptions{
    int WRAP_S = GL_REPEAT;
    int WRAP_T = GL_REPEAT;
    int MIN_FILTER = GL_NEAREST;
    int MAG_FILTER = GL_NEAREST;
};
class Texture {
    unsigned int textureId;
    void setTexture(unsigned char* data, int width, int height, TextureOptions options);
public:
    Texture(std::string filename, struct TextureOptions options);
    Texture(std::string top, std::string front, std::string side, std::string bottom, struct TextureOptions options);
    void bind();
};


#endif //GLFW_TEST_TEXTURE_H
