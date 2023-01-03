#include <iostream>

#include "engine.h"

/*The mian method will create the initial engine so that we can create a new window in order to render
our object. Once the engine is running, it will continue to do so until the key specified in engine.cpp
is pressed. It will then destroy the engine to prevent further issues and end the program.*/
int main(int argc, char** argv)
{
	// Start an engine and run it then cleanup after


	// Create the engine
	Engine* engine = new Engine("Tutorial Window Name", 800, 600);

	// Engine initialization

	if (!engine->Initialize()) {
		printf("The engine failed to start.\n");
		delete engine;
		engine = NULL;
		return 1;
	}

	// Run the engine
	engine->Run();

	// Destroy the engine
	delete engine;
	engine = NULL;

	return 0;
}
