#pragma once
#include "Texture.hpp"

class SceneElement {
	protected:
		int m_posX;
		int m_posY;
		int m_width = 0;
		int m_height = 0;
		Texture* m_texture;

		int m_directionNb = 0;
		int m_animationNb = 0;

	public:
		SceneElement(int posX, int posY);
		~SceneElement();

		void createTexture(GraphicsEngine* graphicsEngine, std::string path, int animationNb = 1, int directionNb = 1);
		void createTexture(GraphicsEngine* graphicsEngine, TTF_Font* font, std::string text, SDL_Color color);
		virtual void display() = 0;
};