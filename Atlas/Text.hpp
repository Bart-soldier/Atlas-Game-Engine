#pragma once

#include "SceneElement.hpp"

class Text : public SceneElement {
	public:
		Text(int posX, int posY, Texture* texture = nullptr);

		void display() override;

		void setText(std::string text, SDL_Color color);
};

