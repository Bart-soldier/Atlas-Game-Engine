// Includes
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include "GraphicsEngine.hpp"
#include "GameplayEngine.hpp"
#include "Constants.hpp"

GraphicsEngine* m_graphicsEngine;
GameplayEngine* m_gameplayEngine;



bool initializeCore() {
	// Create Graphics Engine
	m_graphicsEngine = new GraphicsEngine(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_graphicsEngine == NULL) {
		return false;
	}

	m_gameplayEngine = new GameplayEngine(m_graphicsEngine);

	if (m_gameplayEngine == NULL) {
		return false;
	}
	return true;
}

int main(int argc, char* args[]) {
	if (!initializeCore()) return EXIT_FAILURE;

	m_gameplayEngine->startGame();

	return EXIT_SUCCESS;
}