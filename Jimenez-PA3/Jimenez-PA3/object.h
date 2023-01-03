#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

/*The object.h file defines the methods to initialize, update, and render the object users are trying to create.
the createVertices method will be used to create a various amount of vertices to define what shape the object
is, and will then be rendered.*/
class Object
{
  public:
    Object();
    ~Object();
    void Initialize(GLint posAttribLoc, GLint colAttribLoc);
    void Update(unsigned int dt);
    void Render(GLint posAttribLoc, GLint colAttribLoc);
    void createVertices();

    glm::mat4 GetModel();

    void setSpeed(glm::vec3 spd) { m_speed = spd; }

/*The private variables will be used to move the object at a given speed and will also define it's angle of rotation.*/
  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    GLuint vao;

    GLuint VB;
    GLuint IB;

    glm::vec3 m_speed = glm::vec3(0., 0., 0.);

    float angle;
};

#endif /* OBJECT_H */
