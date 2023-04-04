#include "SceneElement.hpp"

SceneElement::SceneElement(int posX, int posY, Texture* texture) {
	m_posX = posX * TILESIZE * TILEFACTOR;
	m_posY = posY * TILESIZE * TILEFACTOR;
	m_width = 0;
	m_height = 0;
	m_texture = NULL;
	m_directionNb = 0;
	m_animationNb = 0;

	m_sceneElements = nullptr;
	m_sceneElementsWidth = 0;

	if (texture != nullptr) setTexture(texture);
}

bool SceneElement::checkCollision(int posX, int posY) {
	// Get corresponding tile
	int tile_x = posX/(TILESIZE * TILEFACTOR);
	int e_x = tile_x * TILESIZE * TILEFACTOR;
	int tile_y = posY/(TILESIZE * TILEFACTOR);
	int e_y = tile_y * TILESIZE * TILEFACTOR;
	int e_w = e_x + TILESIZE * TILEFACTOR;
	int e_h = e_y + TILESIZE * TILEFACTOR;

	// Check destination
	SceneElement* element = m_sceneElements->at(tile_y * m_sceneElementsWidth + tile_x).second;
	if (element != nullptr) {
		//handleCollision(element);
		return true;
	}

	// Check right tile
	if (posX + m_width > e_w) {
		element = m_sceneElements->at(tile_y * m_sceneElementsWidth + tile_x + 1).second;
		if (element != nullptr) {
			//handleCollision(element);
			return true;
		}
	}

	// Check bottom tile
	if (posY + m_height > e_h) {
		element = m_sceneElements->at((tile_y + 1) * m_sceneElementsWidth + tile_x).second;
		if (element != nullptr) {
			//handleCollision(element);
			return true;
		}
	}

	// Check bottom right tile
	if (posX + m_width > e_w && posY + m_height > e_h) {
		element = m_sceneElements->at((tile_y + 1) * m_sceneElementsWidth + tile_x + 1).second;
		if (element != nullptr) {
			//handleCollision(element);
			return true;
		}
	}

	/*
	if ((e_x <= m_posX && m_posX <= e_x + e_w) || (m_posX <= e_x && e_x <= m_posX + m_width)) {
		if ((e_y <= m_posY && m_posY <= e_y + e_h) || (m_posY <= e_y && e_y <= m_posY + m_height)) {
			//handleCollision(element);
			printf("Collision!\n");
			return true;
		}
	}*/

	return false;
}

void SceneElement::handleCollision(SceneElement* element) {
}

void SceneElement::setTexture(Texture* texture) {
	m_texture = texture;

	m_animationNb = m_texture->getAnimationNb();
	m_directionNb = m_texture->getDirectionNb();

	m_width = m_texture->getWidth() / m_animationNb;
	m_height = m_texture->getHeight() / m_directionNb;
}

void SceneElement::setSceneElements(std::vector<std::pair<SceneElement*, SceneElement*>>* sceneElements, int width) {
	m_sceneElements = sceneElements;
	m_sceneElementsWidth = width;
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