//
// Created by rc_marty on 29.9.23.
//

#include "base_shader.h"
#include <fstream>
#include <string>
#include <cstring>

const char *Base_shader::load_shader(const std::string &vertex_shader_path) {
    std::ifstream file(vertex_shader_path);
    //check if file exists
    if (!file.is_open()) {
        //fprintf(stderr, "Could not open file %s\n", vertex_shader_path.c_str());
        throw std::runtime_error("Could not open shader file " + vertex_shader_path);
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

GLuint Base_shader::compile_shader(GLenum shaderType, const char *shaderSource) {
    printf("[DEBUG] Compiling shader\n");
    printf("_________________________\n");
    GLuint shader_ptr = glCreateShader(shaderType);
    glShaderSource(shader_ptr, 1, &shaderSource, NULL);
    glCompileShader(shader_ptr);


    GLint status;
    glGetShaderiv(shader_ptr, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader_ptr, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader_ptr, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Compiler failure: %s\n", strInfoLog);
        delete[] strInfoLog;
        exit(2);
    }

    return shader_ptr;
}

GLuint Base_shader::link_shader(GLuint &vertex_shader_str, GLuint &fragment_shader_str) {
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
        exit(2);
    }

    return shader_program;
}

Base_shader::Base_shader(const std::string &vertex_shader_path, const std::string &fragment_shader_path) {
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
    printf("[DEBUG] Linked shader %d\n", shader_id);
}


void Base_shader::use_shader() {
    //printf("[DEBUG] Using shader: %d\n", shader_id);
    glUseProgram(shader_id);
}


void Base_shader::unuse_shader() {
    glUseProgram(0);
}

bool Base_shader::set_variable(std::string variable, int value) {
    GLint idUniform = glGetUniformLocation(shader_id, variable.c_str());
    if (idUniform == -1) {
        //fprintf(stderr, "Could not bind VEC3 uniform \"%s\" in shader %d\n", variable.c_str(), shader_id);
        return false;
    }
    glUniform1i(idUniform, value);
    //printf("[DEBUG] Set variable %s\n", variable.c_str());
    //printf("[DEBUG] Set variable %s to %f %f %f\n", variable.c_str(), value.x, value.y, value.z);
    return true;
}

bool Base_shader::set_variable(std::string variable, float value) {
    GLint idUniform = glGetUniformLocation(shader_id, variable.c_str());
    if (idUniform == -1) {
        //fprintf(stderr, "Could not bind VEC3 uniform \"%s\" in shader %d\n", variable.c_str(), shader_id);
        return false;
    }
    glUniform1f(idUniform, value);
    //printf("[DEBUG] Set variable %s\n", variable.c_str());
    //printf("[DEBUG] Set variable %s to %f %f %f\n", variable.c_str(), value.x, value.y, value.z);
    return true;
}

bool Base_shader::set_variable(std::string variable, glm::vec3 value) {
    GLint idUniform = glGetUniformLocation(shader_id, variable.c_str());
    if (idUniform == -1) {
        //fprintf(stderr, "Could not bind VEC3 uniform \"%s\" in shader %d\n", variable.c_str(), shader_id);
        return false;
    }
    glUniform3f(idUniform, value.x, value.y, value.z);
    //printf("[DEBUG] Set variable %s\n", variable.c_str());
    //printf("[DEBUG] Set variable %s to %f %f %f\n", variable.c_str(), value.x, value.y, value.z);
    return true;
}

bool Base_shader::set_variable(std::string variable, glm::vec4 vec) {

    GLint idUniform = glGetUniformLocation(shader_id, variable.c_str());
    if (idUniform == -1) {
        //fprintf(stderr, "Could not bind VEC4 uniform \"%s\" in shader %d\n", variable.c_str(), shader_id);
        return false;
    }
    glUniform4f(idUniform, vec.x, vec.y, vec.z, vec.w);
    //printf("[DEBUG] Set variable %s\n", variable.c_str());
    //printf("[DEBUG] Set variable %s to %f %f %f %f\n", variable.c_str(), vec.x, vec.y, vec.z, vec.w);
    return true;
}

bool Base_shader::set_variable(std::string variable, glm::mat4 matrix) {

    GLint idUniform = glGetUniformLocation(shader_id, variable.c_str());
    if (idUniform == -1) {
        //fprintf(stderr, "Could not bind MAT4 uniform \"%s\" in shader %d\n", variable.c_str(), shader_id);
        return false;
    }
    glUniformMatrix4fv(idUniform, 1, GL_FALSE, &matrix[0][0]);
    return true;
}