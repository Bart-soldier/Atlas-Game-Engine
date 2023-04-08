#include "EventHandler.hpp"

EventHandler::EventHandler(Player* player) {
	m_player = player;
}

bool EventHandler::handleEvent() {
	SDL_Event eventHandler;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&eventHandler) != 0) {
		// User requests quit
		if (eventHandler.type == SDL_QUIT) {
			return true;
		}

		else if (eventHandler.type == SDL_MOUSEBUTTONDOWN) {
			// Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);
			//m_player->move(x, y);
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
	
	return false;
}