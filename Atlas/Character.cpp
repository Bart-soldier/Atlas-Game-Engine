#include "Character.hpp"

Character::Character(GraphicsEngine* graphicsEngine, int x, int y, std::string path, int speedX, int speedY)
	: SceneElement(graphicsEngine, x, y, path) {
	m_speedX = speedX;
	m_speedY = speedY;
}

void Character::move(int direction) {
	switch (direction) {
	case UP:
		m_posY -= m_speedY;
		break;

	case DOWN:
		m_posY += m_speedY;
		break;

	case LEFT:
		m_posX -= m_speedX;
		break;

	case RIGHT:
		m_posX += m_speedX;
		break;
	}
}