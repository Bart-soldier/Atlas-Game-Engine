#include "Character.hpp"

Character::Character(GraphicsEngine* graphicsEngine, int x, int y, std::string path, int speedX, int speedY,
	int animationNb, int directionNb) : SceneElement(graphicsEngine, x, y, path, animationNb, directionNb) {
	m_speedX = speedX;
	m_speedY = speedY;
	m_lastMov = DOWN;

	// Set standard alpha blending
	//m_texture->setBlendMode(SDL_BLENDMODE_BLEND);
}

void Character::display() {
	m_texture->render(m_posX, m_posY, m_lastMov, m_frame);
}

void Character::move(int direction) {
	if (direction == m_lastMov) {
		m_frame++;
		m_frame %= m_animationNb;
	}
	else {
		m_frame = 0;
	}

	switch (direction) {
	case UP:
		m_posY -= m_speedY;
		m_lastMov = UP;
		break;

	case DOWN:
		m_posY += m_speedY;
		m_lastMov = DOWN;
		break;

	case LEFT:
		m_posX -= m_speedX;
		m_lastMov = LEFT;
		break;

	case RIGHT:
		m_posX += m_speedX;
		m_lastMov = RIGHT;
		break;
	}
}