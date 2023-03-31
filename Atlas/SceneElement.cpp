#include "SceneElement.hpp"

SceneElement::SceneElement(int posX, int posY) {
	m_posX = posX * TILESIZE * TILEFACTOR;
	m_posY = posY * TILESIZE * TILEFACTOR;
	m_width = 0;
	m_height = 0;
	m_texture = NULL;
	m_directionNb = 0;
	m_animationNb = 0;
}

void SceneElement::createTexture(GraphicsEngine* graphicsEngine, std::string path, int animationNb, int directionNb) {
	m_texture = new Texture(graphicsEngine, path, animationNb, directionNb);

	m_animationNb = animationNb;
	m_directionNb = directionNb;

	m_width = m_texture->getWidth() / m_animationNb;
	m_height = m_texture->getHeight() / m_directionNb;
}

void SceneElement::createTexture(GraphicsEngine* graphicsEngine, TTF_Font* font, std::string text, SDL_Color color) {
	m_texture = new Texture(graphicsEngine, font, text, color);

	m_animationNb = 1;
	m_directionNb = 1;

	m_width = m_texture->getWidth() / m_animationNb;
	m_height = m_texture->getHeight() / m_directionNb;
}

void SceneElement::setTexture(Texture* texture, int animationNb, int directionNb) {
	m_texture = texture;

	m_animationNb = animationNb;
	m_directionNb = directionNb;

	m_width = m_texture->getWidth() / m_animationNb;
	m_height = m_texture->getHeight() / m_directionNb;
}