#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>
#include <iostream>

void error_callback(int error, const char* desc);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void main() {

	if (!glfwInit()) {
		printf("GLFW Initialization: Failed!\n");
	}

	printf("GLFW Initialization: OK!\n");

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	GLFWwindow* window = glfwCreateWindow(640, 400, "My Window", NULL, NULL);
	if (!window) {
		printf("Window or context creation: Failed!\n");
	}

	glfwMakeContextCurrent(window);

	//Bindkey callback
	glfwSetKeyCallback(window, key_callback);


	//Initialize Glew
	if (glewInit()) {
		printf("GLEW Initialization: Failed!\n");
	}

	glfwSwapInterval(1);

	GLuint Program;
	GLuint vao[1];

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vShaderSrc = "#version 460 \n void main() { gl_position = vec4(0.0, 0.0, 0.0, 1.0); } ";
	const char* fShaderSrc = "#version 460 \n out vec4 color void main() { gl_position = vec4(0.0, 0.3, 1.0, 1.0); } ";

	glShaderSource(vShader, 1, &vShaderSrc, NULL);
	glShaderSource(fShader, 1, &fShaderSrc, NULL);

	glCompileShader(vShader);
	glCompileShader(fShader);

	Program = glCreateProgram();
	glAttachShader(Program, vShader);
	glAttachShader(Program, fShader);

	glLinkProgram(Program);

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);


	//Display Loop
	while (!glfwWindowShouldClose(window)) {
		//display loop runs
		glClearColor(1.0, 0.2, .3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glPointSize(10.f);
		glDrawArrays(GL_POINTS, 0, 1);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//Terminates the glfw object
	glfwDestroyWindow(window);
	glfwTerminate();
}

//Implementing methods
void error_callback(int error, const char* desc) {
	printf("GLFW Error: %s\n", desc);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}