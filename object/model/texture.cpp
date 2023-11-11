//
// Created by rc_marty on 9.11.23.
//

#define STB_IMAGE_IMPLEMENTATION

#include "texture.h"
#include "stb/stb_image.h"


Texture::Texture(const std::string &path, TextureType type, GLenum gl_type) {

    if (type == CUBEMAP) {

        auto files_path = files();

        std::vector<std::string> faces = {
                path + "/" + files_path.right,
                path + "/" + files_path.left,
                path + "/" + files_path.top,
                path + "/" + files_path.bottom,
                path + "/" + files_path.front,
                path + "/" + files_path.back
        };

        GLuint cubemap_texture = load_cubemap(faces);
        printf("id of cubemap texture: %d\n", cubemap_texture);
        printf("path: %s\n", faces[0].c_str());
        this->id = cubemap_texture; // i guess

        return;
    }

    this->load_texture(path, type, gl_type);

}

Texture::Texture(const std::string &path, files files_path, TextureType type, GLenum gl_type) {

    if (type == CUBEMAP) {

        std::vector<std::string> faces = {
                path + "/" + files_path.right,
                path + "/" + files_path.left,
                path + "/" + files_path.top,
                path + "/" + files_path.bottom,
                path + "/" + files_path.front,
                path + "/" + files_path.back
        };

        GLuint cubemap_texture = load_cubemap(faces);
        printf("id of cubemap texture: %d\n", cubemap_texture);
        printf("path: %s\n", faces[0].c_str());
        this->id = cubemap_texture; // i guess

        return;
    }

    this->load_texture(path, type, gl_type);

}

void Texture::bind(int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(gl_type, id);
}

GLenum Texture::get_gl_type() const {
    return gl_type;
}

void Texture::load_texture(const std::string &path, TextureType type, GLenum gl_type) {

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

GLuint Texture::load_cubemap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        } else {
            printf("Cubemap tex failed to load at path: %s\n", faces[i].c_str());
            exit(3);
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
