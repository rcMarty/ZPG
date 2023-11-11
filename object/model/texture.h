//
// Created by rc_marty on 9.11.23.
//

#ifndef ZPG_TEXTURE_H
#define ZPG_TEXTURE_H

#pragma once

#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <vector>

struct files {
    std::string path;
    std::string filename_extension = ".jpg";
    std::string object = "cube.obj";
    std::string right = "right";
    std::string left = "left";
    std::string top = "top";
    std::string bottom = "bottom";
    std::string front = "front";
    std::string back = "back";

    void update_extension() {
        right = right + filename_extension;
        left = left + filename_extension;
        top = top + filename_extension;
        bottom = bottom + filename_extension;
        front = front + filename_extension;
        back = back + filename_extension;
    };
};

enum TextureType {
    DIFFUSE,
    SPECULAR,
    CUBEMAP
};

class Texture {
private:
    GLuint id;
    GLenum gl_type;
    TextureType type;

    void load_texture(const std::string &path, TextureType type, GLenum gl_type);

    GLuint load_cubemap(std::vector<std::string> faces);

public:

    explicit Texture(const std::string &path, TextureType type, GLenum gl_type = GL_TEXTURE_2D);

    explicit Texture(const std::string &path, files files_path, TextureType type, GLenum gl_type = GL_TEXTURE_2D);

    void bind(int slot);

    GLenum get_gl_type() const;

};


#endif //ZPG_TEXTURE_H
