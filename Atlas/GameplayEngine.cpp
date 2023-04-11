#include "GameplayEngine.hpp"

GameplayEngine::GameplayEngine(GraphicsEngine* graphicsEngine) {
	m_graphicsEngine = graphicsEngine;
	m_exitStatus = false;

	// Initialise main camera
	m_graphicsEngine->setCamera(new Camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	// Create player
	m_player = new Player(1, 1, new Texture(m_graphicsEngine, "resources/images/DrJonez.png", 4, 4));
	//player->setWalkingEffect("resources/audio/medium.wav");

	// Create FPS counter
	Texture* fpsTexture = new Texture(m_graphicsEngine, TTF_OpenFont("resources/fonts/roboto/Roboto-Light.ttf", 28),
		"FPS = ", { 0, 0, 0 });
	m_fpsCounter = new Text(0, 0, fpsTexture);
	// Start counting frames per second
	m_fpsTimer.start();
	m_countedFrames = 0;

	m_currentScene = -1;
}

void GameplayEngine::handleEvent() {
	SDL_Event eventHandler;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&eventHandler) != 0) {
		// User requests quit
		if (eventHandler.type == SDL_QUIT) {
			m_exitStatus = true;
		}

		else if (eventHandler.type == SDL_MOUSEBUTTONDOWN) {
			// Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);
			Object* object = checkInteractable(x, y);
			if (object != nullptr) interact(object->interact());
		}

		// User presses a key
		else if (eventHandler.type == SDL_KEYDOWN && eventHandler.key.repeat == 0) {
			switch (eventHandler.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_z:
				m_player->startMovement(NORTH);
				break;

			case SDLK_DOWN:
			case SDLK_s:
				m_player->startMovement(SOUTH);
				break;

			case SDLK_LEFT:
			case SDLK_q:
				m_player->startMovement(WEST);
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				m_player->startMovement(EAST);
				break;

			case SDLK_LSHIFT:
				m_player->toggleRun();
			}
		}

		// User releases a key
		else if (eventHandler.type == SDL_KEYUP && eventHandler.key.repeat == 0) {
			switch (eventHandler.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_z:
				m_player->stopMovement(NORTH);
				break;

			case SDLK_DOWN:
			case SDLK_s:
				m_player->stopMovement(SOUTH);
				break;

			case SDLK_LEFT:
			case SDLK_q:
				m_player->stopMovement(WEST);
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				m_player->stopMovement(EAST);
				break;

			case SDLK_LSHIFT:
				m_player->toggleRun();
			}
		}
	}

	/*
	// Handle event based on current keystate
	if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W]) {
		m_player->move(UP);
	}

	else if (currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S]) {
		m_player->move(DOWN);
	}

	else if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A]) {
		m_player->move(LEFT);
	}

	else if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D]) {
		m_player->move(RIGHT);
	}*/
}

void GameplayEngine::movePlayer() {
	// Get corresponding tile
	int tile_x = m_player->getPosX() / (TILESIZE * TILEFACTOR);
	int tile_y = m_player->getPosY() / (TILESIZE * TILEFACTOR);

	std::vector<SceneElement*> neighbors = m_scenes.at(m_currentScene)->getNeighborForegroundElements(tile_x, tile_y);

	m_player->move(neighbors);

	Camera* camera = m_graphicsEngine->getCamera();
	Scene* currentScene = m_scenes.at(m_currentScene);

	if (camera != NULL) {
		if (!currentScene->isInterior())
			camera->centerOn(m_player->getPosX(), m_player->getPosY(), m_player->getWidth(), m_player->getHeight(),
				currentScene->getWidth() * TILESIZE * TILEFACTOR, currentScene->getHeight() * TILESIZE * TILEFACTOR);
		else camera->centerOn(m_player->getPosX(), m_player->getPosY(), m_player->getWidth(), m_player->getHeight());
	}
}

void GameplayEngine::enterScene() {
	// Place player
	std::pair<int, int> entryPoint = m_scenes.at(m_currentScene)->getEntry();
	m_player->setPos(entryPoint.first, entryPoint.second);

	// Play music
	m_scenes.at(m_currentScene)->playTheme();
}

void GameplayEngine::leaveScene() {
	m_scenes.at(m_currentScene)->stopTheme();
}

Object* GameplayEngine::checkInteractable(int x, int y) {
	Camera* camera = m_graphicsEngine->getCamera();
	int posX = m_player->getPosX();
	int posY = m_player->getPosY();

	int trueX = camera->getPosX() + x;
	int trueY = camera->getPosY() + y;
	int diffX = (trueX > posX) ? trueX - posX : posX - trueX;
	int diffY = (trueY > posY) ? trueY - posY : posY - trueY;

	// If object is within reach
	if (diffX <= 2 * TILESIZE * TILEFACTOR && diffY < 2 * TILESIZE * TILEFACTOR) {
		int gridX = trueX / (TILESIZE * TILEFACTOR);
		int gridY = trueY / (TILESIZE * TILEFACTOR);

		Object* object = m_scenes.at(m_currentScene)->getSceneElementForeground(gridX, gridY);

		if (object != nullptr) {
			if(object->isInteractable()) return object;
		}
	}

	return nullptr;
}

void GameplayEngine::interact(std::pair<int, int> interaction) {
	if (interaction.first = CHANGE_SCENE) {
		leaveScene();
		m_currentScene = interaction.second;
		enterScene();
	}
}

void GameplayEngine::gameLoop() {
	// Start FPS cap timer
	m_fpsCapTimer.start();

	// Calculate and correct fps
	float avgFPS = m_countedFrames / (m_fpsTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000) avgFPS = 0;
	m_fpsCounter->setText("FPS = " + std::to_string((int)avgFPS), { 255, 255, 255 });

	update();

	display();

	++m_countedFrames;

	// If frame finished early
	Uint32 frameTicks = m_fpsCapTimer.getTicks();
	if (frameTicks < TICKS_PER_FRAME) {
		// Wait remaining time
		SDL_Delay(static_cast<Uint32>(TICKS_PER_FRAME - frameTicks));
	}
}

void GameplayEngine::update() {
	// Handle events on queue
	handleEvent();

	m_scenes.at(m_currentScene)->update();

	movePlayer();
}

void GameplayEngine::display() {
	m_graphicsEngine->clearScreen();

	m_scenes.at(m_currentScene)->display();

	m_player->display();

	// Render FPS counter
	m_fpsCounter->display();

	// Update screen
	m_graphicsEngine->updateScreen();
}

void GameplayEngine::startGame() {
	// Tomb exterior
	m_scenes.push_back(new Scene(m_graphicsEngine));
	m_scenes.back()->testLevel1();
	m_scenes.back()->setTheme("resources/audio/IndianaJones.wav");

	// Tomb interior
	m_scenes.push_back(new Scene(m_graphicsEngine));
	m_scenes.back()->testLevel2();
	m_scenes.back()->setTheme("resources/audio/Tomb.wav");

	// Start at tomb exterior
	m_currentScene = 0;
	enterScene();

	// Main loop
	while (!m_exitStatus && m_currentScene != -1) {
		gameLoop();
	}
}