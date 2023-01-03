#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
//Including "Pyramid.h" didn't work for me as it kept throwing errors. To fix this
//I ctrl + . and added the recommended file location
#include "../../Jimenez-PA3/Jimenez-PA3/Pyramid.h"
#include <stack>


/*The graphics class will be used to render the object and display it in the window. It will be calling
upon the object of type Object and will be used to get the location of the triangle.*/
class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Render(float dt, glm::vec3 speed, GLFWwindow* window);

    Object* getInteractWith();
    Pyramid* returningPyramid();

    stack<glm::mat4> mvStack;

    Object* getCube() { return m_triangle; }
    Object* getMoon() { return m_moon; }
    Pyramid* getPyramid() { return m_pyramid; }

/*The private variables are for determining the camera and shader being used, as well as
the objects projection matrices.*/
  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    glm::mat4 viewMat;
    GLint m_modelMatrix;
    GLint m_vertPos;
    GLint m_vertCol;
    GLint m_positionAttrib;
    GLint m_colorAttrib;

    Object* m_triangle;
    Object* m_moon;
    Pyramid* m_pyramid;


};

#endif /* GRAPHICS_H */
