#pragma once
#include <SDL.h>
#include "window.hpp"

//Key press surfaces constants
enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

class EventHandler {
	private:
		Window* m_window;
		SDL_Event m_eventHandler;
		//The images that correspond to a keypress
		SDL_Surface* m_keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

	public:
		EventHandler(Window* window);
		void handleEvent();
};

