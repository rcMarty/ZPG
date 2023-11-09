//
// Created by rc_marty on 9.11.23.
//

#include "texture.h"
#include "stb/stb_image.h"


Texture::Texture(const std::string &path, TextureType type, GLenum gl_type) {

    this->type = type;
    this->gl_type = gl_type;

    //load image
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        GLenum gl_channel;
        if (nrChannels == 1) {
            gl_channel = GL_RED;
        } else if (nrChannels == 3) {
            gl_channel = GL_RGB;
        } else {
            gl_channel = GL_RGBA;
        }
        glGenTextures(1, &this->id);
        glBindTexture(gl_type, this->id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, gl_channel, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture: %s\n", path.c_str());
        exit(1);
    }
    printf("id of texture: %d\n", this->id);
    stbi_image_free(data);

}

void Texture::bind(int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(gl_type, id);
}

GLenum Texture::get_gl_type() const {
    return gl_type;
}