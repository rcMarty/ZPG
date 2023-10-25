//
// Created by rc_marty on 30.9.23.
//

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "stdio.h"
#include "stdlib.h"
#include "../resources/models/square.h"
#include <memory>
#include <vector>
#include <string>
#include <glm/vec4.hpp>

class Mesh {

private:
    GLuint VAO = 0, VBO = 0, EBO = 0;
    uint vertices_describe_count = 0;
    uint color_describe_count = 0;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;


    static void claculate_indices(Mesh &mesh);

public:

    Mesh(std::vector<GLfloat> vertices, uint vertices_describe_count = 3, uint color_describe_count = 3);


    explicit Mesh(std::string path);

    Mesh(const float vertices[], uint count);

    Mesh(const point vertices[], uint count);

    void init();

    void render();

};