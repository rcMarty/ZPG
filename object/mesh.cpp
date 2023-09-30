//
// Created by rc_marty on 30.9.23.
//

#include "mesh.h"

Mesh::Mesh(std::vector<GLfloat> vertices, uint vertices_describe_count, uint color_describe_count) {
    this->vertices = vertices;
    this->vertices_describe_count = vertices_describe_count;
    this->color_describe_count= color_describe_count;
}

Mesh::Mesh(const point vertices[]) {
    //convert vertices to vector
    std::vector<GLfloat> vertices_vec;
//    printf("size of: %d\n", sizeof(vertices)/4/8);
//    printf("size of verticies: %d\n", sizeof(vertices));

    for (int i = 0; i < sizeof(vertices)/2; i++) {
        for (int j = 0; j < 4; ++j) {
            vertices_vec.push_back(vertices[i].pos[j]);
        }
        for (int j = 0; j < 4; ++j) {
            vertices_vec.push_back(vertices[i].color[j]);
        }
    }
    this->vertices = vertices_vec;
    this->vertices_describe_count = 4;
    this->color_describe_count= 4;
}

void Mesh::init() {
//    printf("size of vertices: %d\n", vertices.size());
//    printf("verticies describe count: %d\n", vertices_describe_count);
//    printf("color describe count: %d\n", color_describe_count);

    //generate vertex array object and vertex buffer object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //bind vertex array object and vertex buffer object
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    //set vertex attribute pointers
    glVertexAttribPointer(0, vertices_describe_count, GL_FLOAT, GL_FALSE, (vertices_describe_count+color_describe_count) * sizeof(GLfloat), (GLvoid *) nullptr);
    glEnableVertexAttribArray(0);

    //todo color
    // temporary solution
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, color_describe_count, GL_FLOAT, GL_FALSE, (vertices_describe_count+color_describe_count) * sizeof(GLfloat), (GLvoid *)(vertices_describe_count*sizeof (GLfloat)));

    //enable depth


}

void Mesh::render() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

Mesh::Mesh(const float *vertices, uint count ) {
    //convert vertices to vector

//    printf("size of: %d\n", count);
//    printf("size of verticies: %d\n", count);

    std::vector<GLfloat> vertices_vec;
    for (int i = 0; i < count;++i) {
        vertices_vec.push_back(vertices[i]);
    }
    //printf("size of vertices_vec: %d\n", vertices_vec.size());

    this->vertices = vertices_vec;
    this->vertices_describe_count = 3;
    this->color_describe_count= 3;

}

