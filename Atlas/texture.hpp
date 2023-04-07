#pragma once
#include "GraphicsEngine.hpp"
#include <vector>

class Texture {
	private:
		// The actual hardware texture
		SDL_Texture* m_texture;

		// The Graphics Engine
		GraphicsEngine* m_graphicsEngine;

		// Image dimensions
		int m_width;
		int m_height;
		// Alpha
		Uint8 m_alpha;

		// Number of directions and animations
		int m_directionNb;
		int m_animationNb;
		// x, y, width, height
		std::vector<SDL_Rect> m_spriteClips;

		TTF_Font* m_font = NULL;

		// Deallocates texture
		void free();
		// Initialize Sprite Clips
		void intializeSpriteClips();

	public:
		// Initializes variables
		Texture(GraphicsEngine* graphicsEngine, TTF_Font* font, std::string text, SDL_Color color, int animationNb = 1,
			int directionNb = 1);
		Texture(GraphicsEngine* graphicsEngine, std::string path, int animationNb = 1, int directionNb = 1);
		// Deallocates memory
		~Texture();

		// Loads image at specified path
		bool loadFromFile(std::string path);
		// Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

		// Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		// Set blend mode
		void setBlendMode(SDL_BlendMode blendMode);
		// Set alpha modulation
		void setAlpha(int alpha);
		// Renders texture at given point
		void render(int x, int y, int lastMov = 0, int frame = 0, bool toCamera = true);

		// Gets image dimensions
		int getWidth();
		int getHeight();
		Uint8 getAplha();
		int getDirectionNb();
		int getAnimationNb();
};

