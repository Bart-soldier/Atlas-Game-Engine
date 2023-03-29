#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <cmath>

class GraphicsEngine {
	private:
		// The window we'll be rendering to
		SDL_Window* m_window = NULL;

		// The window renderer
		SDL_Renderer* m_renderer = NULL;

		// Screen dimension constants
		int m_width;
		int m_height;

		bool m_exitStatus = false;

		Mix_Music* testMusic = NULL;

	public:
		GraphicsEngine(int width, int height);
		~GraphicsEngine();
		SDL_Texture* createTexture(SDL_Surface* surface);
		void render(SDL_Texture* texture, int x, int y, SDL_Rect* clip = NULL);
		void clearScreen();
		void updateScreen();
		void drawRectangle();

		int getWidth();
		int getHeight();
		bool getExitStatus();
		void setExitStatus(bool exitStatus);
};
