#include "Character.hpp"

Character::Character(GraphicsEngine* graphicsEngine, int x, int y, std::string path, int speedX, int speedY)
	: SceneElement(graphicsEngine, x, y, path) {
	m_speedX = speedX;
	m_speedY = speedY;
	m_lastMov = DOWN;
	m_width = m_texture->getWidth()/ANIMATION_FRAMES;
	m_height = m_texture->getHeight()/TOTAL_DIRECTIONS;
	
	for (int y = 0; y < TOTAL_DIRECTIONS; y ++) {
		for (int x = 0; x < ANIMATION_FRAMES; x++) {
			printf("Test = %d", x + y);
			m_spriteClips[(y * ANIMATION_FRAMES) + x].x = x * m_width;
			m_spriteClips[(y * ANIMATION_FRAMES) + x].y = y * m_height;
			m_spriteClips[(y * ANIMATION_FRAMES) + x].w = m_width;
			m_spriteClips[(y * ANIMATION_FRAMES) + x].h = m_height;
		}
	}

	// Set standard alpha blending
	//m_texture->setBlendMode(SDL_BLENDMODE_BLEND);
}

void Character::display() {
	m_texture->render(m_posX, m_posY, &m_spriteClips[(m_lastMov * ANIMATION_FRAMES) + m_frame]);
}

void Character::move(int direction) {
	if (direction == m_lastMov) {
		m_frame++;
		m_frame %= ANIMATION_FRAMES;
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