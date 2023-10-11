//
// Created by rc_marty on 29.9.23.
//

#include "shader.h"
#include <fstream>
#include <string>
#include <cstring>

const char *Shader::load_shader(const std::string &vertex_shader_path) {
    std::ifstream file(vertex_shader_path);
    //check if file exists
    if (!file.is_open()) {
        fprintf(stderr, "Could not open file %s\n", vertex_shader_path.c_str());
        return nullptr;
    }
    std::string str;
    std::string file_contents;
    while (std::getline(file, str)) {
        file_contents += str;
        file_contents.push_back('\n');
    }
    char *shader = new char[file_contents.length() + 1];
    strcpy(shader, file_contents.c_str());
    return shader;
}

GLuint Shader::compile_shader(GLenum shaderType, const char *shaderSource) {
    printf("[DEBUG] Compiling shader\n");
    printf("_________________________\n");
    GLuint shader_ptr = glCreateShader(shaderType);
    glShaderSource(shader_ptr, 1, &shaderSource, NULL);
    glCompileShader(shader_ptr);

    return shader_ptr;
}

GLuint Shader::link_shader(GLuint &vertex_shader_str, GLuint &fragment_shader_str) {
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader_str);
    glAttachShader(shader_program, fragment_shader_str);
    glLinkProgram(shader_program);

    // check for errors
    GLint status;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shader_program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    return shader_program;
}

Shader::Shader(std::shared_ptr<Camera> camera, const std::string &vertex_shader_path, const std::string &fragment_shader_path) {
    this->camera = camera;
    this->camera->attach_shader(std::shared_ptr<Shader>(this));

    printf("Creating shader\n");
    printf("_________________________\n");
    auto vertex_shader = load_shader(vertex_shader_path);
    auto fragment_shader = load_shader(fragment_shader_path);
    printf("vertex_shader : %s\n", vertex_shader);
    printf("fragment_shader : %s\n", fragment_shader);
    GLuint vertex = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    GLuint fragment = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    delete[] vertex_shader;
    delete[] fragment_shader;

    shader_id = link_shader(vertex, fragment);
    printf("[DEBUG] Linked shader\n");
}

void Shader::set_variable(std::string variable, glm::mat4 matrix) {

    GLint idUniform = glGetUniformLocation(shader_id, variable.c_str());
    if (idUniform == -1) {
        fprintf(stderr, "Could not bind uniform %s\n", variable.c_str());
        return;
    }
    glUniformMatrix4fv(idUniform, 1, GL_FALSE, &matrix[0][0]);

}


void Shader::use_shader() {
    //printf("[DEBUG] Using shader: %d\n", shader_id);
    glUseProgram(shader_id);
}

void Shader::update_camera() {

    use_shader();
    set_variable("viewMatrix", camera->get_view_matrix());
    set_variable("projectionMatrix", camera->get_projection_matrix());

    printf("[DEBUG] Camera updated in shader: %d\n", shader_id);

}



