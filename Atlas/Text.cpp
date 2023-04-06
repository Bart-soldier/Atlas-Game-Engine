#include "Text.hpp"

Text::Text(int posX, int posY, Texture* texture) : SceneElement(posX, posY, texture) {
}

void Text::setText(std::string text, SDL_Color color) {
	m_texture->loadFromRenderedText(text.c_str(), color);

	m_width = m_texture->getWidth() / m_animationNb;
	m_height = m_texture->getHeight() / m_directionNb;
}