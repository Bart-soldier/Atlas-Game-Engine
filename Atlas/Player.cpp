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

void Player::setCamera(Camera* camera) {
	m_camera = camera;
}