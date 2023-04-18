#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"

/*The graphics class will be used to render the object and display it in the window. It will be calling
upon the object of type Object and will be used to get the location of the triangle.*/
class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt, glm::vec3 speed);
    void Render();

    Object* getInteractWith();

    Object* getTriangle() { return m_triangle; }

/*The private variables are for determining the camera and shader being used, as well as
the objects projection matrices.*/
  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    GLint m_vertPos;
    GLint m_vertCol;

    Object* m_triangle;

};

#endif /* GRAPHICS_H */
