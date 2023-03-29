#include "Text.hpp"

Text::Text(GraphicsEngine* graphicsEngine, int posX, int posY, std::string fontPath, float fontSize, std::string text,
	SDL_Color color)
	: SceneElement(posX, posY) {
	createTexture(graphicsEngine, TTF_OpenFont(fontPath.c_str(), fontSize), text, color);
}

void Text::display() {
	m_texture->render(m_posX, m_posY);
}