#include "SceneElement.hpp"

SceneElement::SceneElement(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path, int animationNb, int directionNb) {
	m_posX = posX;
	m_posY = posY;
	m_texture = new Texture(graphicsEngine, path, animationNb, directionNb);

	m_animationNb = animationNb;
	m_directionNb = directionNb;

	m_width = m_texture->getWidth() / m_animationNb;
	m_height = m_texture->getHeight() / m_directionNb;
}

SceneElement::~SceneElement() {
	m_texture->free();
}