#pragma once
#include "GraphicsEngine.hpp"
#include <vector>

class Texture {
	private:
		// The actual hardware texture
		SDL_Texture* m_texture;

		// The Graphics Engine
		GraphicsEngine* m_graphicsEngine;

		// Object dimension
		int m_objWidth;
		int m_objHeight;

		// Image dimensions
		int m_width;
		int m_height;
		// Alpha
		Uint8 m_alpha;

		// Sprite info
		int m_spriteLineNb;
		int m_spriteColumnNb;
		std::vector<SDL_Rect> m_spriteClips;
		std::string m_path;

		TTF_Font* m_font = NULL;

		// Deallocates texture
		void free();
		void reset();
		// Initialize Sprite Clips
		void intializeSpriteClips();

	public:
		// Text texture
		Texture(GraphicsEngine* graphicsEngine, TTF_Font* font, std::string text, SDL_Color color);
		// Image texture
		Texture(GraphicsEngine* graphicsEngine, std::string path, int spriteColumnNb = 1, int spriteLineNb = 1);
		// Deallocates memory
		~Texture();

		// Loads image at specified path
		bool loadFromFile(std::string path);
		// Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

		bool resize(int width, int height);

		// Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		// Set blend mode
		void setBlendMode(SDL_BlendMode blendMode);
		// Set alpha modulation
		void setAlpha(int alpha);
		// Renders texture at given point
		void render(int x, int y, int width, int height, int spriteLineIndex = 0, int spriteColumnIndex = 0, bool toCamera = true);

		// Gets image dimensions
		int getWidth();
		int getHeight();
		Uint8 getAplha();
		int getSpriteLineNb();
		int getSpriteColumnNb();
};

