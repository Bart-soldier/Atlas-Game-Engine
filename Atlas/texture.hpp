#pragma once
#include "GraphicsEngine.hpp"

class Texture {
	private:
		// The actual hardware texture
		SDL_Texture* m_texture;

		// The Graphics Engine
		GraphicsEngine* m_graphicsEngine;

		// Image dimensions
		int m_width = 0;
		int m_height = 0;

		// Alpha
		Uint8 m_alpha = 255;

	public:
		// Initializes variables
		Texture(GraphicsEngine* graphicsEngine);
		Texture(GraphicsEngine* graphicsEngine, std::string path);
		// Deallocates memory
		~Texture();

		// Loads image at specified path
		bool loadFromFile(std::string path);
		// Deallocates texture
		void free();
		// Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		// Set blend mode
		void setBlendMode(SDL_BlendMode blendMode);
		// Set alpha modulation
		void setAlpha(int alpha);
		// Renders texture at given point
		void render(int x, int y, SDL_Rect* clip = NULL);

		// Gets image dimensions
		int getWidth();
		int getHeight();
		Uint8 getAplha();
};

