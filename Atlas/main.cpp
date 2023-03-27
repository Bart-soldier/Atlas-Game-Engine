// Includes
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include "GraphicsEngine.hpp"
#include "texture.hpp"
#include "eventhandler.hpp"

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

	Texture* fooTexture = new Texture(graphicsEngine);
	Texture* backgroundTexture = new Texture(graphicsEngine);

	fooTexture->loadFromFile("resources/foo.png");
	backgroundTexture->loadFromFile("resources/background.png");

	// Main loop
	while (!exitStatus) {
		// Handle events on queue
		exitStatus = eventHandler->handleEvent();

		graphicsEngine->clearScreen();

		// Render background texture to screen
		backgroundTexture->render(0, 0);

		// Render Foo' to the screen
		fooTexture->render(240, 190);

		// Update screen
		graphicsEngine->updateScreen();
	}

	return EXIT_SUCCESS;
}