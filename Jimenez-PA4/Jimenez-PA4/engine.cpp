
#include "engine.h"
#include "graphics.h"

Engine::Engine(const char* name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;

}


Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT);
  if(!m_window->Initialize())
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  m_camera = m_graphics->m_camera;
  if (!m_camera->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
      printf("Camera Failed to Initialize\n");
      return false;
  }

  glfwSetCursorPosCallback(m_window->getWindow(), cursorPositionCallBack);
  glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while (!glfwWindowShouldClose(m_window->getWindow()))
  {
      ProcessInput();
      Display(m_window->getWindow(), glfwGetTime());
      glfwPollEvents();
  }
  m_running = false;

}

void Engine::ProcessInput()
{
    double xpos, ypos;
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window->getWindow(), true);

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_UP) == GLFW_RELEASE &&
        glfwGetKey(m_window->getWindow(), GLFW_KEY_DOWN) == GLFW_RELEASE &&
        glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT) == GLFW_RELEASE &&
        glfwGetKey(m_window->getWindow(), GLFW_KEY_RIGHT) == GLFW_RELEASE) {
        m_graphics->m_camera->Update(glm::vec3(0., 0., 0.));
    }

    const float cameraSpeed = .05f;
    m_camera->GetView();
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        m_graphics->m_camera->cameraPos += cameraSpeed * m_graphics->m_camera->cameraFront;
        m_graphics->m_camera->Update(glm::vec3(0., .1, 0.));
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        m_graphics->m_camera->cameraPos -= cameraSpeed * m_graphics->m_camera->cameraFront;
        m_graphics->m_camera->Update(glm::vec3(0., -.1, 0.));
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        m_graphics->m_camera->cameraPos -= glm::normalize(glm::cross(m_graphics->m_camera->cameraFront, m_graphics->m_camera->cameraUp)) * cameraSpeed;
        m_graphics->m_camera->Update(glm::vec3(.1, 0., 0.));
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        m_graphics->m_camera->cameraPos += glm::normalize(glm::cross(m_graphics->m_camera->cameraFront, m_graphics->m_camera->cameraUp)) * cameraSpeed;
        m_graphics->m_camera->Update(glm::vec3(-.1, 0., 0.));
    }
}

unsigned int Engine::getDT()
{
  //long long TimeNowMillis = GetCurrentTimeMillis();
  //assert(TimeNowMillis >= m_currentTimeMillis);
  //unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  //m_currentTimeMillis = TimeNowMillis;
  //return DeltaTimeMillis;
    return glfwGetTime();
}

long long Engine::GetCurrentTimeMillis()
{
  //timeval t;
  //gettimeofday(&t, NULL);
  //long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  //return ret;
    return (long long) glfwGetTime();
}

void Engine::Display(GLFWwindow* window, double time) {

    m_graphics->Render();
    m_window->Swap();
    //m_graphics->HierarchicalUpdate2(time);
}

void cursorPositionCallBack(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    bool firstMouse = true;
    float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0 / 2.0;
    glm::vec3 cameraFront = glm::vec3(0.0, 0.0, 0.0);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
