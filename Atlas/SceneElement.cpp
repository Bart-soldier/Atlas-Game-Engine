#include "SceneElement.hpp"

SceneElement::SceneElement(int posX, int posY, Texture* texture) {
	m_posX = posX * TILESIZE * TILEFACTOR;
	m_posY = posY * TILESIZE * TILEFACTOR;
	m_width = 0;
	m_height = 0;
	m_texture = NULL;

	m_directionNb = 0;
	m_animationNb = 0;
	m_frame = 0;
	m_timeSinceLastMov = 0;

	m_sceneElements = nullptr;
	m_sceneElementsWidth = 0;

	if (texture != nullptr) setTexture(texture);
}

void SceneElement::display() {
	if (m_texture != NULL) {
		m_texture->render(m_posX, m_posY);
	}
}

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