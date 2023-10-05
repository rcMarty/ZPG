//
// Created by rc_marty on 30.9.23.
//

#include "mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


void Mesh::claculate_indices(Mesh &mesh) {
    int verticies_count = mesh.vertices.size() / (mesh.vertices_describe_count + mesh.color_describe_count);
    //printf("verticies count: %d\n", verticies_count);
    for (int i = 0; i < verticies_count; ++i) {
        mesh.indices.push_back(i);
    }
    //printf("size of indices: %d\n", mesh.indices.size());
}


Mesh::Mesh(std::vector<GLfloat> vertices, uint vertices_describe_count, uint color_describe_count) {
    this->vertices = vertices;
    this->vertices_describe_count = vertices_describe_count;
    this->color_describe_count= color_describe_count;
    Mesh::claculate_indices(*this);
}

Mesh::Mesh(const point vertices[], uint count) {
    //convert vertices to vector
    std::vector<GLfloat> vertices_vec;
    printf("size of: %d\n", count   );
    printf("size of vertices: %ld\n", sizeof(vertices));

    for (size_t i = 0; i < count; i++) {
        for (float po: vertices[i].pos) {
            vertices_vec.push_back(po);
        }
        for (float j: vertices[i].color) {
            vertices_vec.push_back(j);
        }
    }
    this->vertices = vertices_vec;
    this->vertices_describe_count = 4;
    this->color_describe_count= 4;

    Mesh::claculate_indices(*this);
}

void Mesh::init() {
//    printf("size of vertices: %d\n", vertices.size());
//    printf("verticies describe count: %d\n", vertices_describe_count);
//    printf("color describe count: %d\n", color_describe_count);

    // create vao
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // create vbo
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);


    // set vertex attributes
    glVertexAttribPointer(0, vertices_describe_count, GL_FLOAT, GL_FALSE, (vertices_describe_count + color_describe_count) * sizeof(GLfloat), (GLvoid*) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, color_describe_count, GL_FLOAT, GL_FALSE, (vertices_describe_count + color_describe_count) * sizeof(GLfloat), (GLvoid*)(vertices_describe_count * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // create ebo
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


}

void Mesh::render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);


}

Mesh::Mesh(const float *vertices, uint count ) {
    //convert vertices to vector

//    printf("size of: %d\n", count);
//    printf("size of verticies: %d\n", count);

    std::vector<GLfloat> vertices_vec;
    for (size_t i = 0; i < count; ++i) {
        vertices_vec.push_back(vertices[i]);
    }
    //printf("size of vertices_vec: %d\n", vertices_vec.size());
    this->vertices = vertices_vec;
    this->vertices_describe_count = 3;
    this->color_describe_count= 3;

    Mesh::claculate_indices(*this);

}

Mesh::Mesh(std::string path) {
    printf("[DEBUG] Loading mesh from: %s\n", path.c_str());
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        printf("[ERROR] ERROR::ASSIMP::%s\n", importer.GetErrorString());
        return;
    }


    printf("\tobject has %d meshes\n", scene->mNumMeshes);
    printf("\tobject has %d meshes on index 0\n", scene->mMeshes[0]);
    for (size_t m = 0; m < scene->mNumMeshes; ++m) {
        auto mesh = scene->mMeshes[0];

        for (size_t i = 0; i < mesh->mNumVertices; ++i) {

            auto &vector = mesh->mVertices[i];
            auto &colors = mesh->mNormals[i];

            this->vertices.push_back(vector.x);
            this->vertices.push_back(vector.y);
            this->vertices.push_back(vector.z);
            this->vertices.push_back(colors.x);
            this->vertices.push_back(colors.y);
            this->vertices.push_back(colors.z);
        }

        for (size_t i = 0; i < mesh->mNumFaces; ++i) {
            aiFace face = mesh->mFaces[i];
            this->indices.push_back(face.mIndices[2]);
            this->indices.push_back(face.mIndices[1]);
            this->indices.push_back(face.mIndices[0]);
        }

    }

    printf("\tno of vertices: %ld\n", this->vertices.size() / 6);
    printf("\tno of indices: %ld\n", this->indices.size());

    this->vertices_describe_count = 3;
    this->color_describe_count= 3;

}


