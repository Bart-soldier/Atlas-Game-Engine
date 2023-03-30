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
#include "Wall.hpp"

//const int SCREEN_FPS = 60;
//const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

GraphicsEngine* m_graphicsEngine;
EventHandler* m_eventHandler;
Player* m_player;
std::vector<SceneElement*> m_sceneElements;

Text* m_fpsCounter;
Timer m_fpsTimer;
int m_countedFrames;

int exitStatus = false;

bool initializeCore() {
	// Create Graphics Engine
	m_graphicsEngine = new GraphicsEngine(640, 480);

	if (m_graphicsEngine == NULL) {
		return false;
	}

	// Create player
	m_player = new Player(m_graphicsEngine, 0, m_graphicsEngine->getHeight()/4, "resources/images/animated_character.png", 1, 1, 2);
	//player->setWalkingEffect("resources/audio/medium.wav");

	//Create EventHandler
	m_eventHandler = new EventHandler(m_player);

	// Create FPS counter
	m_fpsCounter = new Text(m_graphicsEngine, 0, 0, "resources/fonts/roboto/Roboto-Light.ttf", 28, "FPS = ",
		{ 0, 0, 0 });
	// Start counting frames per second
	m_fpsTimer.start();
	m_countedFrames = 0;

	return true;
}

void createSceneElements() {
	// Create scene elements
	m_sceneElements.push_back(new Environment(m_graphicsEngine, 0, 0, "resources/images/background.png"));
	//background->setTheme("resources/audio/theme.wav");
	//background->playTheme();

	m_sceneElements.push_back(new Wall(m_graphicsEngine, m_graphicsEngine->getWidth() / 2, m_graphicsEngine->getHeight() / 2,
		"resources/images/wall.png"));
}

void loop() {
	// Handle events on queue
	exitStatus = m_eventHandler->handleEvent();

	// Calculate and correct fps
	float avgFPS = m_countedFrames / (m_fpsTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000) {
		avgFPS = 0;
	}
	m_fpsCounter->setText("FPS = " + std::to_string((int)avgFPS));

	m_graphicsEngine->clearScreen();

	// Render every scene element
	for (auto sceneElement = m_sceneElements.begin(); sceneElement != m_sceneElements.end(); ++sceneElement) {
		(*sceneElement)->display();
	}

	// Render player
	m_player->display();

	// Render FPS counter
	m_fpsCounter->display();

	// Update screen
	m_graphicsEngine->updateScreen();

	++m_countedFrames;
}

int main(int argc, char* args[]) {
	if (!initializeCore()) return EXIT_FAILURE;

	createSceneElements();

	// Main loop
	while (!exitStatus) {
		loop();
	}

	return EXIT_SUCCESS;
}