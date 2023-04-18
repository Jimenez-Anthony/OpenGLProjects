#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <stack>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "pyramid.h"
#include "Mesh.h"
#include "Sphere.h"

#define numVBOs 2;
#define numIBs 2;


class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(double dt);
    void HierarchicalUpdate(double dt);
    void HierarchicalUpdate2(double dt);
    void Render();
    Camera* m_camera;    
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    Shader* m_shader;


  private:
    std::string ErrorString(GLenum error);

    bool collectShPrLocs();
    void ComputeTransforms (double dt, std::vector<float> speed, std::vector<float> dist,
        std::vector<float> rotSpeed, glm::vec3 rotVector, std::vector<float> scale, 
        glm::mat4& tmat, glm::mat4& rmat, glm::mat4& smat);

    stack<glm::mat4> modelStack;

    GLint m_modelMatrix;
    GLint m_positionAttrib;
    GLint m_colorAttrib;

    Object *m_cube;
    Object *m_cube2;
    Mesh* m_mesh;
    Sphere* m_sphere;
    Sphere* m_sphere2;
 

};

#endif /* GRAPHICS_H */
