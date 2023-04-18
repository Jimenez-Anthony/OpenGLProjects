
#include "engine.h"

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

/*Initialize will create a new window, given the width and height, and will then start the graphics to initialize the cube
within that window.*/
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

 
  // No errors
  return true;
}

/*The run method will continuously run the window until a certain key is pressed. Until that key is pressed, the window
will remain open and will continue to render the given object.*/
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

/*ProcessInput method will be used to take in user input in order to move the object within the window.*/
void Engine::ProcessInput()
{
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window->getWindow(), true);

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_UP) == GLFW_RELEASE &&
        glfwGetKey(m_window->getWindow(), GLFW_KEY_DOWN) == GLFW_RELEASE &&
        glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT) == GLFW_RELEASE &&
        glfwGetKey(m_window->getWindow(), GLFW_KEY_RIGHT) == GLFW_RELEASE)
        m_graphics->getTriangle()->setSpeed(glm::vec3(0., 0., 0.));
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
        m_graphics->getTriangle()->setSpeed(glm::vec3(0., .1, 0.));
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
        m_graphics->getTriangle()->setSpeed(glm::vec3(0., -.1, 0.));
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
        m_graphics->getTriangle()->setSpeed(glm::vec3(.1, 0., 0.));
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        m_graphics->getTriangle()->setSpeed(glm::vec3(-.1, 0., 0.));


}

/*getDT will be used to get the delta time of the window.*/
unsigned int Engine::getDT()
{
  //long long TimeNowMillis = GetCurrentTimeMillis();
  //assert(TimeNowMillis >= m_currentTimeMillis);
  //unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  //m_currentTimeMillis = TimeNowMillis;
  //return DeltaTimeMillis;
    return glfwGetTime();
}

/*This method will be used to return the delta time in milliseconds.*/
long long Engine::GetCurrentTimeMillis()
{
  //timeval t;
  //gettimeofday(&t, NULL);
  //long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  //return ret;
    return (long long) glfwGetTime();
}

/*The display method will call on render, swap, and update in order to display the rendered object onto the window.*/
void Engine::Display(GLFWwindow* window, double time) {

    m_graphics->Render();

    m_window->Swap();

    m_graphics->Update(time, speed);
}
