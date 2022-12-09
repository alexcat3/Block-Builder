//
// Created by alexc on 11/10/2022.
//

#include "Texture.h"
#include <stb_image.h>

Texture::Texture(std::string filename, struct TextureOptions options) {
    //Load the image into *data. Get its width and height
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 4);
    setTexture(data, width, height, options);
    stbi_image_free(data);
}


Texture::Texture(std::string top, std::string middle, std::string bottom, struct TextureOptions options){
    int width1, height1, nrChannels1;
    int width2, height2, nrChannels2;
    int width3, height3, nrChannels3;
    unsigned char *data1 = stbi_load(top.c_str(), &width1, &height1, &nrChannels1, 4);
    unsigned char *data2 = stbi_load(middle.c_str(), &width2, &height2, &nrChannels2,4);
    unsigned char *data3 = stbi_load(bottom.c_str(), &width3, &height3, &nrChannels3, 4);
    if(width1 != width2 || width2 != width3){
        throw std::invalid_argument("Texture widths must be equal");
    }


    unsigned char* data = (unsigned char*)malloc(width1*(height1+height2+height3)*4);

    memcpy(data, data1, width1*height1*4);
    memcpy(data+width1*height1*4, data2, width1*height2*4);
    memcpy(data+width1*(height1+height2)*4, data3, width1*height3*4);
    stbi_image_free(data1);
    stbi_image_free(data2);
    stbi_image_free(data3);
    setTexture(data, width1, height1+height2+height3, options);

    free(data);
}

void Texture::setTexture(unsigned char *data, int width, int height, struct TextureOptions options){
    //Create a new empty texture and bind it to GL_TEXTURE_2D
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, options.WRAP_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, options.WRAP_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, options.MIN_FILTER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, options.MAG_FILTER);
    //Initialize the texture with data from the image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, textureId);
}

