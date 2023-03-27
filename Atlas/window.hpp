#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Window {
	private:
		// The window we'll be rendering to
		SDL_Window* m_window = NULL;

		// The window renderer
		SDL_Renderer* m_renderer = NULL;

		// Screen dimension constants
		int m_width;
		int m_height;

		bool m_exitStatus = false;

	public:
		Window(int width, int height);
		void close();
		SDL_Texture* loadTexture(std::string path);
		void unloadTexture(SDL_Texture* texture);
		void updateWindow(SDL_Texture* texture);
		//void updateWindow(SDL_Texture* texture, int x, int y, int width, int height);

		SDL_Window* getWindow();
		bool getExitStatus();
		void setExitStatus(bool exitStatus);
};
