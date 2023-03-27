#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "GraphicsEngine.hpp"

class Texture {
private:
	// The actual hardware texture
	SDL_Texture* m_texture;

	// The Graphics Engine
	GraphicsEngine* m_graphicsEngine;

	// Image dimensions
	int m_width;
	int m_height;

	public:
		// Initializes variables
		Texture(GraphicsEngine* graphicsEngine);
		// Deallocates memory
		~Texture();

		// Loads image at specified path
		bool loadFromFile(std::string path);
		// Deallocates texture
		void free();
		// Renders texture at given point
		void render(int x, int y);

		// Gets image dimensions
		int getWidth();
		int getHeight();
};

