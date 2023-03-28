#include "EventHandler.hpp"

EventHandler::EventHandler(Player* player) {
	m_player = player;
}

bool EventHandler::handleEvent() {
	SDL_Event eventHandler;

	while (SDL_PollEvent(&eventHandler) != 0) {
		// User requests quit
		if (eventHandler.type == SDL_QUIT) {
			return true;
		}

		// User presses a key
		else if (eventHandler.type == SDL_KEYDOWN) {
			//Select surfaces based on key press
			switch (eventHandler.key.keysym.sym) {
			case SDLK_UP:
				m_player->move(UP);
				break;

			case SDLK_DOWN:
				m_player->move(DOWN);
				break;

			case SDLK_LEFT:
				m_player->move(LEFT);
				break;

			case SDLK_RIGHT:
				m_player->move(RIGHT);
				break;

			default:
				break;
			}
		}
	}
	
	return false;
}