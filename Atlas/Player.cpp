#include "Player.hpp"

Player::Player(int posX, int posY, Texture* texture) : Character(posX, posY, texture) {
	m_camera = NULL;
}

void Player::move() {
	Character::move();

	if (m_camera != NULL) {
		if (!m_scene->isInterior()) m_camera->centerOn(m_posX, m_posY, m_width, m_height,
			m_scene->getWidth() * TILESIZE * TILEFACTOR, m_scene->getHeight() * TILESIZE * TILEFACTOR);
		else m_camera->centerOn(m_posX, m_posY, m_width, m_height);
	}
}

bool Player::checkInteractable(int x, int y) {
	int trueX = m_camera->getPosX() + x;
	int trueY = m_camera->getPosY() + y;
	int diffX = (trueX > m_posX) ? trueX - m_posX : m_posX - trueX;
	int diffY = (trueY > m_posY) ? trueY - m_posY : m_posY - trueY;

	// If object is within reach
	if (diffX <= 2 * TILESIZE * TILEFACTOR && diffY < 2 * TILESIZE * TILEFACTOR) {
		int gridX = trueX / (TILESIZE * TILEFACTOR);
		int gridY = trueY / (TILESIZE * TILEFACTOR);

		Object* object = m_scene->getSceneElementForeground(gridX, gridY);

		if (object != nullptr) return object->isInteractable();
	}

	return false;
}

void Player::setCamera(Camera* camera) {
	m_camera = camera;
}