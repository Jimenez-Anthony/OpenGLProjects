#ifndef MESH_H
#define MESH_H

#include <vector>
#include "graphics_headers.h"
#include "Texture.h"

class Mesh
{
public:
    Mesh();
    Mesh(glm::vec3 pivot, float scale, const char* fname);
    Mesh(glm::vec3 pivot, float scale, const char* fname, const char* tname);

    ~Mesh();
    void Update(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
    void Render(GLint posAttrib, GLint colAttrib);
    void Render(GLint positionAttribLoc, GLint colorAttribLoc, GLint tcAttribLoc, GLint hasTex);

    glm::mat4 GetModel();

    bool InitBuffers();
    bool loadModelFromFile(const char* path);

    void setupModelMatrix(glm::vec3 pivot, float angle, float scale);

    bool hasTex;
    GLuint getTextureID() { return m_texture->getTextureID(); }



private:
    glm::vec3 pivotLocation;
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    Texture* m_texture;

    GLuint vao;

    float angle;
};

#endif