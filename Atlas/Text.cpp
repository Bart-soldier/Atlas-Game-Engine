#include "Text.hpp"

Text::Text(GraphicsEngine* graphicsEngine, int posX, int posY, std::string fontPath, float fontSize, std::string text,
	SDL_Color color)
	: SceneElement(posX, posY) {
	createTexture(graphicsEngine, TTF_OpenFont(fontPath.c_str(), fontSize), text, color);
	m_color = color;
}

void Text::display() {
	m_texture->render(m_posX, m_posY);
}

void Text::setText(std::string text) {
	m_texture->loadFromRenderedText(text.c_str(), m_color);

	m_width = m_texture->getWidth() / m_animationNb;
	m_height = m_texture->getHeight() / m_directionNb;
}