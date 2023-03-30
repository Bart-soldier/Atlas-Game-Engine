// Includes
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include "GraphicsEngine.hpp"
#include "EventHandler.hpp"
#include "Player.hpp"
#include "Environment.hpp"
#include "Text.hpp"
#include "Timer.hpp"

int main(int argc, char* args[]) {
	// Create Window
	GraphicsEngine* graphicsEngine = new GraphicsEngine(640, 480);
	// Create player
	Player* player = new Player(graphicsEngine, 240, 190, "resources/images/animated_character.png", 1, 1, 2);
	//player->setWalkingEffect("resources/audio/medium.wav");

	//Create EventHandler
	EventHandler* eventHandler = new EventHandler(player);

	// FPS Counter
	Timer fpsTimer;
	// Start counting frames per second
	int countedFrames = 0;
	fpsTimer.start();

	int exitStatus = false;

	if (graphicsEngine == NULL) {
		return EXIT_FAILURE;
	}

	Environment* background = new Environment(graphicsEngine, 0, 0, "resources/images/background.png");
	//background->setTheme("resources/audio/theme.wav");
	//background->playTheme();

	Text* text = new Text(graphicsEngine, 0, 0, "resources/fonts/roboto/Roboto-Light.ttf", 28, "FPS = ",
		{ 0, 0, 0 });

	// Main loop
	while (!exitStatus) {
		// Handle events on queue
		exitStatus = eventHandler->handleEvent();

		//Calculate and correct fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000) {
			avgFPS = 0;
		}
		text->setText("FPS = " + std::to_string((int) avgFPS));

		graphicsEngine->clearScreen();

		// Render background texture to screen
		background->display();

		// Render Foo' to the screen
		player->display();

		// Render text
		text->display();

		// Update screen
		graphicsEngine->updateScreen();

		++countedFrames;
	}

	return EXIT_SUCCESS;
}