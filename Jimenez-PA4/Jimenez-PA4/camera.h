#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"


class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::mat4 projection;
    glm::mat4 view;
    void Update(glm::vec3 speed);
};

#endif /* CAMERA_H */
