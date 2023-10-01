//
// Created by rc_marty on 29.9.23.
//
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <vector>

class Shader
{
public:

    static GLuint create_shader(const std::string &vertex_shader_path,const std::string &fragment_shader_path);
    static const char *load_shader(const std::string &vertex_shader_path);
    static GLuint compile_shader( GLenum shader_type, const char*shader_source);
    static GLuint link_shader(GLuint &vertex_shader, GLuint &fragment_shader);

};
