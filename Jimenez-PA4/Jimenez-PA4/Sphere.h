#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "graphics_headers.h"
#include <cmath>

class Sphere
{
public:
    Sphere(int prec);
    Sphere();
    ~Sphere();

    int getNumVertices();
    int getNumIndices();
    std::vector<unsigned int> getIndices();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec2> getTexCoords();
    std::vector<glm::vec3> getNormals();

    void Update(glm::mat4 model);
    void Render(GLint posAttrib, GLint colAttrib);
    void setupVertices(int prec);

    glm::mat4 GetModel();

    bool InitBuffers();

private:
    glm::vec3 pivotLocation;
    glm::mat4 model;
    int numVertices;
    int numIndices;
    std::vector<glm::vec3> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    float toRadians(float degrees);

    GLuint VB;
    GLuint IB;

    GLuint vao;


    float angle;
};

#endif /* OBJECT_H */