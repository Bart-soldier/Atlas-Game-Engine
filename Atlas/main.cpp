// Includes
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include "GraphicsEngine.hpp"
#include "EventHandler.hpp"
#include "Player.hpp"
#include "Text.hpp"
#include "Timer.hpp"
#include "Scene.hpp"
#include "Constants.hpp"

GraphicsEngine* m_graphicsEngine;
EventHandler* m_eventHandler;
Player* m_player;
Scene* level1;

Text* m_fpsCounter;
Timer m_fpsTimer;
int m_countedFrames;

// FPS Caping
Timer m_fpsCapTimer;

int exitStatus = false;

bool initializeCore() {
	// Create Graphics Engine
	m_graphicsEngine = new GraphicsEngine(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_graphicsEngine == NULL) {
		return false;
	}

	Camera* camera = new Camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	m_graphicsEngine->setCamera(camera);

	//m_grameplayEngine = new GameplayEngine(

	// Create player
	Texture* playerImg = new Texture(m_graphicsEngine, "resources/images/DrJonez.png", 4, 4);
	m_player = new Player(1, 1, playerImg);
	m_player->setCamera(camera);
	
	//player->setWalkingEffect("resources/audio/medium.wav");

	//Create EventHandler
	m_eventHandler = new EventHandler(m_player);

	// Create FPS counter
	Texture* fpsTexture = new Texture(m_graphicsEngine, TTF_OpenFont("resources/fonts/roboto/Roboto-Light.ttf", 28),
		"FPS = ", { 0, 0, 0 });
	m_fpsCounter = new Text(0, 0, fpsTexture);
	// Start counting frames per second
	m_fpsTimer.start();
	m_countedFrames = 0;

	return true;
}

void loop() {
	// Start FPS cap timer
	m_fpsCapTimer.start();

	// Calculate and correct fps
	float avgFPS = m_countedFrames / (m_fpsTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000) {
		avgFPS = 0;
	}
	m_fpsCounter->setText("FPS = " + std::to_string((int)avgFPS), { 255, 255, 255 });

	m_graphicsEngine->clearScreen();

	// Handle events on queue
	exitStatus = m_eventHandler->handleEvent();

	level1->update();

	level1->display();

	m_player->move();

	m_player->display();

	// Render FPS counter
	m_fpsCounter->display();

	// Update screen
	m_graphicsEngine->updateScreen();

	++m_countedFrames;

	// If frame finished early
	int frameTicks = m_fpsCapTimer.getTicks();
	if (frameTicks < TICKS_PER_FRAME) {
		// Wait remaining time
		SDL_Delay(TICKS_PER_FRAME - frameTicks);
	}
}

int main(int argc, char* args[]) {
	if (!initializeCore()) return EXIT_FAILURE;

	level1 = new Scene(m_graphicsEngine);
	level1->testLevel2();
	m_player->addToScene(level1);
	//level1->setTheme("resources/audio/IndianaJones.wav");
	//level1->playTheme();

	// Main loop
	while (!exitStatus) {
		loop();
	}

	return EXIT_SUCCESS;
}