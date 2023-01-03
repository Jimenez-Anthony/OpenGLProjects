#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
    //--Init the view and projection matrices
    //  if you will be having a moving camera the view matrix will need to more dynamic
    //  ...Like you should update it before you render more dynamic 
    //  for this project having them static will be fine
    view = glm::lookAt(glm::vec3(x, y, z), //Eye Position
        glm::vec3(0.0, 0.0, 0.0), //Focus point
        glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up
    //
  //view = glm::lookAt(cameraPos, cameraFront  + cameraPos, cameraUp);

    projection = glm::perspective(glm::radians(40.f), //the FoV typically 90 degrees is good which is what this is set to
        float(w) / float(h), //Aspect Ratio, so Circles stay Circular
        0.01f, //Distance to the near plane, normally a small value like this
        100.0f); //Distance to the far plane, 
    width = w;
    height = h;
    return true;
}

glm::mat4 Camera::GetProjection()
{
    return projection;
}

glm::mat4 Camera::GetView()
{
    return view;
}
void Camera::Update(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float fov)
{
    view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);
    projection = glm::perspective(glm::radians(fov), //the FoV typically 90 degrees is good which is what this is set to
        float(width) / float(height), //Aspect Ratio, so Circles stay Circular
        0.01f, //Distance to the near plane, normally a small value like this
        100.0f);


}