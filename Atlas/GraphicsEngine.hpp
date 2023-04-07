#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Camera.hpp"

#define TILESIZE 16
#define TILEFACTOR 4

class GraphicsEngine {
	private:
		// The window we'll be rendering to
		SDL_Window* m_window;

		// The window renderer
		SDL_Renderer* m_renderer;

		// Screen dimension constants
		int m_width;
		int m_height;

		// Camera
		Camera* m_camera;

		bool m_exitStatus = false;

	public:
		GraphicsEngine(int width, int height);
		~GraphicsEngine();
		SDL_Texture* createTexture(SDL_Surface* surface);
		void render(SDL_Texture* texture, int x, int y, int width, int height, SDL_Rect* clip = NULL, bool toCamera = true);
		void clearScreen();
		void updateScreen();
		void drawRectangle();

		int getWidth();
		int getHeight();
		bool getExitStatus();
		void setExitStatus(bool exitStatus);
		void setCamera(Camera* camera);
};
