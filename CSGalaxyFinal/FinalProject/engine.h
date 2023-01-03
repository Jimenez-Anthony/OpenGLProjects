#ifndef ENGINE_H
#define ENGINE_H


#include <assert.h>
#include "window.h"
#include "graphics.h"

static void cursorPositionCallBack(GLFWwindow*, double xpos, double ypos);

static bool firstMouse = true;
static float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
static float pitch = 0.0f;
static float lastX = 800.0f / 2.0;
static float lastY = 600.0 / 2.0;
static float fov = 45.0f;
static double x = 0.0;
static double y = 20.0;
static double z = 5.0;
static glm::vec3 cameraPos = glm::vec3(x, y, z);
static glm::vec3 cameraFront = glm::vec3(0.0f, -1.0f, 0.0f);
static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
class Engine
{
public:
    Engine(const char* name, int width, int height);

    ~Engine();
    bool Initialize();
    void Run();
    void ProcessInput();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
    void Display(GLFWwindow*, double);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);



private:
    // Window related variables
    Window* m_window;
    const char* m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;


    Graphics* m_graphics;

    bool m_running;
};

#endif // ENGINE_H
