#pragma once
#include "Texture.hpp"

class SceneElement {
	protected:
		int m_posX;
		int m_posY;
		int m_width;
		int m_height;
		Texture* m_texture;

		int m_directionNb;
		int m_animationNb;

	public:
		SceneElement(int posX, int posY);
		~SceneElement();

		void createTexture(GraphicsEngine* graphicsEngine, std::string path, int animationNb = 1, int directionNb = 1);
		void createTexture(GraphicsEngine* graphicsEngine, TTF_Font* font, std::string text, SDL_Color color);
		virtual void display() = 0;
};