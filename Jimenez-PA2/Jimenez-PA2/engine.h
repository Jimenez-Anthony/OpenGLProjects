#ifndef ENGINE_H
#define ENGINE_H


#include <assert.h>
#include "window.h"
#include "graphics.h"


/*The engine class will be used to define the various methods in order to create the window, run the program, and to process
user input in order to move the object on the screen. The setSpeed method will be used to set the speed and direction of
an object on button click.*/
class Engine
{
  public:
    Engine(const char*  name, int width, int height);
    
    ~Engine();
    bool Initialize();
    void Run();
    void ProcessInput();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
    void Display(GLFWwindow*, double);

   
    void setSpeed(glm::vec3 spd) { speed = spd; };

  
/*The private section will define the variables used to create the window, such as it's width and height.*/
  private:
    // Window related variables
    Window *m_window;    
    const char* m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;

    glm::vec3 speed = glm::vec3(0.f,0.f,0.f);


    Graphics *m_graphics;

    bool m_running;
};

#endif // ENGINE_H
