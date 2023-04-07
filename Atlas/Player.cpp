#include "Player.hpp"

Player::Player(int posX, int posY, int speedX, int speedY, Texture* texture) : Character(posX, posY, speedX, speedY, texture) {
	m_camera = NULL;
}

void Player::move(int direction) {
	Character::move(direction);

	if (m_camera != NULL) {
		m_camera->centerOn(m_posX, m_posY, m_width, m_height);
	}
}

void Player::move(int x, int y) {
	Character::move(x, y);

	if (m_camera != NULL) {
		m_camera->centerOn(m_posX, m_posY, m_width, m_height);
	}
}

void Player::setCamera(Camera* camera) {
	m_camera = camera;
	m_camera->centerOn(m_posX, m_posY, m_width, m_height);
}