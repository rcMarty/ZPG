//
// Created by rc_marty on 9.11.23.
//

#ifndef ZPG_TEXTURE_H
#define ZPG_TEXTURE_H

#pragma once

#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION

enum TextureType {
    DIFFUSE,
    SPECULAR,
};

class Texture {
private:
    GLuint id;
    GLenum gl_type;
    TextureType type;

public:

    explicit Texture(const std::string &path, TextureType type, GLenum gl_type = GL_TEXTURE_2D);

    void bind(int slot);

    GLenum get_gl_type() const;

};


#endif //ZPG_TEXTURE_H
