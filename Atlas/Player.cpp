#include "Player.hpp"

Player::Player(int posX, int posY, Texture* texture) : Character(posX, posY, texture) {
	m_camera = NULL;
}

void Player::move() {
	Character::move();

	if (m_camera != NULL) {
		m_camera->centerOn(m_posX, m_posY, m_width, m_height);
	}
}

void Player::setCamera(Camera* camera) {
	m_camera = camera;
	m_camera->centerOn(m_posX, m_posY, m_width, m_height);
}