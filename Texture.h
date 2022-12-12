//
// Created by alexc on 11/10/2022.
//

#ifndef GLFW_TEST_TEXTURE_H
#define GLFW_TEST_TEXTURE_H
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
//Represents the opengl options that can be used for the texture
struct TextureOptions{
    int WRAP_S = GL_REPEAT;
    int WRAP_T = GL_REPEAT;
    int MIN_FILTER = GL_NEAREST;
    int MAG_FILTER = GL_NEAREST;
};
class Texture {
    //Id assigned to the texture by OpenGL
    unsigned int textureId;
    //Initializes the texture using the given RGBA bitmap image of widthxheight with given options
    void setTexture(unsigned char* data, int width, int height, TextureOptions options);
public:
    //Creates a new texture from the given image files
    Texture(std::string filename, struct TextureOptions options);
    //Vertically concatenate the given 4 images to create a texture
    //Used for cubes with 4 distinct faces
    Texture(std::string top, std::string front, std::string side, std::string bottom, struct TextureOptions options);
    void bind();
};


#endif //GLFW_TEST_TEXTURE_H
