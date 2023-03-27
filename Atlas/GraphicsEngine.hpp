#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

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

	public:
		GraphicsEngine(int width, int height);
		~GraphicsEngine();
		SDL_Texture* createTexture(SDL_Surface* surface);
		void render(SDL_Texture* texture, int x, int y, int width, int height);
		void clearScreen();
		void updateScreen();
		void drawRectangle();

		int getWidth();
		int getHeight();
		bool getExitStatus();
		void setExitStatus(bool exitStatus);
};