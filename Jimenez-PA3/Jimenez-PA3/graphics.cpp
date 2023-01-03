#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

/*The initialize method will initialize the required objects so that users can view the object in the window.
Items such as the camera and shader are used to create a viewport where we can see the triangle once it's created.*/
bool Graphics::Initialize(int width, int height)
{

  // For OpenGL 3

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  // Find where vertex attributes are in shader
  m_vertPos = m_shader->GetAttribLocation("v_position");
  m_vertCol = m_shader->GetAttribLocation("v_color");

  m_positionAttrib = m_shader->GetAttribLocation("v_position");
  m_colorAttrib = m_shader->GetAttribLocation("v_color");

  // Create the object
  m_triangle = new Object();
  m_triangle->Initialize(m_vertPos, m_vertCol);

  m_moon = new Object();
  m_moon->Initialize(m_vertPos, m_vertCol);
  
  m_pyramid = new Pyramid();
  m_pyramid->Initialize(m_vertPos, m_vertCol);

  
  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

/*The Render method will render the object onto a new window. It will first lear the screen of any previous shader
objects, and then render the object by sending in the projection matrix.*/
void Graphics::Render(float dt, glm::vec3 speed, GLFWwindow* window)
{
  //clear the screen
  glClearColor(0.5, 0.2, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(1, 0, 0));
  mvStack.push(viewMat);

  mvStack.push(mvStack.top());
  mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(.0f, .0f, .0f));
  mvStack.push(mvStack.top());
  mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)dt, glm::vec3(1.0f, .0f, .0f));
  mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
  m_pyramid->Render(m_vertPos, m_vertCol);
  mvStack.pop();

  mvStack.push(mvStack.top());
  mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)dt) * 4.0, 0.0f, cos((float)dt) * 4.0));
  mvStack.push(mvStack.top());
  mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)dt, glm::vec3(.0, 1.0, .0));
  mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(.8f, .8f, .8f));
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
  m_triangle->Render(m_vertPos,m_vertCol);
  mvStack.pop();

  mvStack.push(mvStack.top());
  mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(.0f, sin((float)dt) * 2.0, cos((float)dt) * 2.0));
  mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)dt, glm::vec3(.0, .0, 1.0));
  mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(.45f, .45f, .45f));
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
  m_moon->Render(m_vertPos, m_vertCol);

  m_triangle->Update(dt);
  m_pyramid->Update(dt);
  m_moon->Update(dt);

  mvStack.pop(); mvStack.pop(); mvStack.pop(); mvStack.pop();

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}


Object* Graphics::getInteractWith() {
    return m_triangle;
}

Pyramid* Graphics::returningPyramid() {
    return m_pyramid;
}

/*The errorstring method will return any specified errors that the user experiences when attempting to render the object.*/
std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}
