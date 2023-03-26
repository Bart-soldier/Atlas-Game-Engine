#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>

class Window {
	private:
		//The window we'll be rendering to
		SDL_Window* m_window = NULL;

		//The surface contained by the window
		SDL_Surface* m_surface = NULL;

		// Screen dimension constants
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;

		bool m_exitStatus = false;

	public:
		Window();
		void close();
		SDL_Surface* loadSurface(std::string path);
		void unloadSurface(SDL_Surface* surface);
		void updateSurface(SDL_Surface* surface);

		SDL_Window* getWindow();
		SDL_Surface* getSurface();
		bool getExitStatus();
		void setExitStatus(bool exitStatus);
};
