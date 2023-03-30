#pragma once

#include "SceneElement.hpp"

class Text : public SceneElement {
	private:
		SDL_Color m_color;

	public:
		Text(GraphicsEngine* graphicsEngine, int posX, int posY, std::string fontPath, float fontSize, std::string text,
			SDL_Color color);

		void display();
		void setText(std::string text);
};

