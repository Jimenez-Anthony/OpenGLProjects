#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <stack>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "sphere.h"
#include "mesh.h"

#define numVBOs 2;
#define numIBs 2;


class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void HierarchicalUpdate2(double dt);
    void Render();


    Camera* m_camera;
    Camera* getCamera() { return m_camera; }
    Mesh* getMesh() { return m_mesh; }

  private:
    std::string ErrorString(GLenum error);

    bool collectShPrLocs();
    void ComputeTransforms (double dt, std::vector<float> speed, std::vector<float> dist,
        std::vector<float> rotSpeed, glm::vec3 rotVector, std::vector<float> scale, 
        glm::mat4& tmat, glm::mat4& rmat, glm::mat4& smat);

    stack<glm::mat4> modelStack;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    GLint m_positionAttrib;
    GLint m_colorAttrib;
    GLint m_tcAttrib;
    GLint m_hasTexture;

    //Planets
    Sphere* m_sphere;
    Sphere* m_sphere2;
    Sphere* m_sphere3;
    Sphere* m_merc;
    Sphere* m_venus;
    Sphere* m_mars;
    Sphere* m_jupiter;
    Sphere* m_saturn;
    Sphere* m_uranus;
    Sphere* m_neptune;
    Sphere* m_backDrop;

    //Comet
    Sphere* m_comet;

    //Dwarf planets
    Sphere* m_ceres;
    Sphere* m_Eris;
    Sphere* m_haumea;

    //Moons
    Sphere* m_mars_m1;
    Sphere* m_mars_m2;

    Sphere* m_Europa;
    Sphere* m_Io;
    Sphere* m_Callisto;

    Sphere* m_Titan;
    Sphere* m_Rhea;

    Sphere* m_Titania;
    Sphere* m_Oberon;

    Sphere* m_Triton;
    Sphere* m_Nereid;

    //Skybox
    Sphere* m_skybox;

    Mesh* m_mesh;



};

#endif /* GRAPHICS_H */
