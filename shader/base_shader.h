//
// Created by rc_marty on 29.9.23.
//
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <vector>

#include "../object/camera/camera.h"
#include "observer.h"

class Camera;

class Base_shader : public Observer {
private:
    GLint shader_id;

    static const char *load_shader(const std::string &vertex_shader_path);

    static GLuint compile_shader(GLenum shader_type, const char *shader_source);

    static GLuint link_shader(GLuint &vertex_shader, GLuint &fragment_shader);

public:

    Base_shader(const std::string &vertex_shader_path, const std::string &fragment_shader_path);

    virtual ~Base_shader() = default;

    void use_shader();

    void unuse_shader();

    virtual void update() override = 0;

    void set_variable(std::string variable, glm::mat4 value);

    void set_variable(std::string variable, glm::vec4 value);

    void set_variable(std::string variable, glm::vec3 value);

    void set_variable(std::string variable, float value);

    void set_variable(std::string variable, int value);
};
