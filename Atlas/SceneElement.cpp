#include "SceneElement.hpp"

SceneElement::SceneElement(int posX, int posY, Texture* texture) {
	m_posX = posX * TILESIZE * TILEFACTOR;
	m_posY = posY * TILESIZE * TILEFACTOR;
	m_width = 0;
	m_height = 0;
	m_texture = NULL;
	m_directionNb = 0;
	m_animationNb = 0;

	if (texture != nullptr) setTexture(texture);
}

void SceneElement::setTexture(Texture* texture) {
	m_texture = texture;

	m_animationNb = m_texture->getAnimationNb();
	m_directionNb = m_texture->getDirectionNb();

	m_width = m_texture->getWidth() / m_animationNb;
	m_height = m_texture->getHeight() / m_directionNb;
}