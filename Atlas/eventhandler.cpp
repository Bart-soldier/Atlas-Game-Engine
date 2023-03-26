#include "eventhandler.hpp"

EventHandler::EventHandler(Window* window) {
	m_window = window;

	//Load default surface
	m_keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = m_window->loadSurface("resources/press.bmp");
	if (m_keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		printf("Failed to load default image!\n");
	}

	//Load up surface
	m_keyPressSurfaces[KEY_PRESS_SURFACE_UP] = m_window->loadSurface("resources/up.bmp");
	if (m_keyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
		printf("Failed to load up image!\n");
	}

	//Load down surface
	m_keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = m_window->loadSurface("resources/down.bmp");
	if (m_keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf("Failed to load down image!\n");
	}

	//Load left surface
	m_keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = m_window->loadSurface("resources/left.bmp");
	if (m_keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
		printf("Failed to load left image!\n");
	}

	//Load right surface
	m_keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = m_window->loadSurface("resources/right.bmp");
	if (m_keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		printf("Failed to load right image!\n");
	}

	//Set default current surface
	m_window->updateSurface(m_keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]);
}

void EventHandler::handleEvent() {
	while (SDL_PollEvent(&m_eventHandler) != 0) {
		//User requests quit
		if (m_eventHandler.type == SDL_QUIT) {
			m_window->setExitStatus(true);
			//Deallocate surfaces
			for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
				m_window->unloadSurface(m_keyPressSurfaces[i]);
			}
		}

		//User presses a key
		else if (m_eventHandler.type == SDL_KEYDOWN) {
			//Select surfaces based on key press
			switch (m_eventHandler.key.keysym.sym) {
			case SDLK_UP:
				m_window->updateSurface(m_keyPressSurfaces[KEY_PRESS_SURFACE_UP]);
				break;

			case SDLK_DOWN:
				m_window->updateSurface(m_keyPressSurfaces[KEY_PRESS_SURFACE_DOWN]);
				break;

			case SDLK_LEFT:
				m_window->updateSurface(m_keyPressSurfaces[KEY_PRESS_SURFACE_LEFT]);
				break;

			case SDLK_RIGHT:
				m_window->updateSurface(m_keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT]);
				break;

			default:
				m_window->updateSurface(m_keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]);
				break;
			}
		}
	}
}