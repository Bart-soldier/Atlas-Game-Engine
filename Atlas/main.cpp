// Includes
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include "GraphicsEngine.hpp"
#include "EventHandler.hpp"
#include "Character.hpp"
#include "Environment.hpp"

int main(int argc, char* args[]) {
	// Create Window
	GraphicsEngine* graphicsEngine = new GraphicsEngine(640, 480);
	//Create EventHandler
	//EventHandler* m_eventHandler = new EventHandler(m_window);
	EventHandler* eventHandler = new EventHandler();

	int exitStatus = false;

	if (graphicsEngine == NULL) {
		return EXIT_FAILURE;
	}

	Character* player = new Character(graphicsEngine, 240, 190, "resources/foo.png");
	Environment* background = new Environment(graphicsEngine, 0, 0, "resources/background.png");

	// Main loop
	while (!exitStatus) {
		// Handle events on queue
		exitStatus = eventHandler->handleEvent();

		graphicsEngine->clearScreen();

		// Render background texture to screen
		background->display();

		// Render Foo' to the screen
		player->display();

		// Update screen
		graphicsEngine->updateScreen();
	}

	return EXIT_SUCCESS;
}