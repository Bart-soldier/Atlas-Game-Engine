#include "SceneElement.hpp"

SceneElement::SceneElement(int posX, int posY, Texture* texture) {
	m_posX = posX * TILESIZE * TILEFACTOR;
	m_posY = posY * TILESIZE * TILEFACTOR;
	m_width = TILESIZE * TILEFACTOR;
	m_height = TILESIZE * TILEFACTOR;
	m_texture = NULL;

	m_hitBox.x = m_posX;
	m_hitBox.y = m_posY;
	m_hitBox.w = m_width;
	m_hitBox.h = m_height;

	m_frame = 0;
	m_timeSinceLastFrame = 0;

	if (texture != nullptr) setTexture(texture);
}

void SceneElement::display() {
	if (m_texture != NULL) {
		m_texture->render(m_posX, m_posY);
	}
}
/*
bool SceneElement::checkCollision(int posX, int posY) {
	// Get corresponding tile
	int tile_x = posX/(TILESIZE * TILEFACTOR);
	int tile_y = posY/(TILESIZE * TILEFACTOR);
	SceneElement* element = m_sceneElements->at(tile_y * m_sceneElementsWidth + tile_x).second;

	// Check destination
	if (element != nullptr) {
		handleCollision(element);
		return true;
	}

	/*
	if ((e_x <= m_posX && m_posX <= e_x + e_w) || (m_posX <= e_x && e_x <= m_posX + m_width)) {
		if ((e_y <= m_posY && m_posY <= e_y + e_h) || (m_posY <= e_y && e_y <= m_posY + m_height)) {
			//handleCollision(element);
			printf("Collision!\n");
			return true;
		}
	}*/
/*
	return false;
}

void SceneElement::handleCollision(SceneElement* element) {
}*/

void SceneElement::setTexture(Texture* texture) {
	m_texture = texture;

	m_width = m_texture->getWidth() / m_texture->getSpriteColumnNb();
	m_height = m_texture->getHeight() / m_texture->getSpriteLineNb();

	m_hitBox.w = m_width;
	m_hitBox.h = m_height;
}

int SceneElement::getPosX() {
	return m_posX;
}

int SceneElement::getPosY() {
	return m_posY;
}

int SceneElement::getWidth() {
	return m_width;
}

int SceneElement::getHeight() {
	return m_height;
}

SDL_Rect SceneElement::getHitBox() {
	return m_hitBox;
}

void SceneElement::setPos(int x, int y) {
	m_posX = x;
	m_posY = y;
}