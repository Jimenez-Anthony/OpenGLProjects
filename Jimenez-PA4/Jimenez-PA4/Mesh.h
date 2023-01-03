#ifndef MESH_H
#define MESH_H

#include <vector>
#include "graphics_headers.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh
{
public:
    Mesh();
    Mesh(glm::vec3 pivot);
    Mesh(glm::vec3 pivot, float angle, float scale);

    ~Mesh();
    void Update(glm::mat4 model);
    void Render(GLint posAttrib, GLint colAttrib);

    glm::mat4 GetMesh();

    bool InitBuffers();
    bool CreateMesh( const char*);

    struct Vertex {
        glm::vec3 vertex;
        glm::vec3 color;

        Vertex(glm::vec3 v, glm::vec3 c) : vertex(v), color(c) {}
    };

private:
    glm::vec3 pivotLocation;
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    GLuint vao;

    float angle;
    void setupModelMatrix(glm::vec3 pivotLoc, float angle, float scale);
};

#endif
