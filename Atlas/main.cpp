// Includes
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include "GraphicsEngine.hpp"
#include "EventHandler.hpp"
#include "Player.hpp"
#include "Environment.hpp"

int main(int argc, char* args[]) {
	// Create Window
	GraphicsEngine* graphicsEngine = new GraphicsEngine(640, 480);
	// Create player
	Player* player = new Player(graphicsEngine, 240, 190, "resources/foo.png", 5, 5);

	//Create EventHandler
	EventHandler* eventHandler = new EventHandler(player);

	int exitStatus = false;

	if (graphicsEngine == NULL) {
		return EXIT_FAILURE;
	}

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