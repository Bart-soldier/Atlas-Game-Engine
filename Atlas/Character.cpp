#include "Character.hpp"

Character::Character(int posX, int posY, int speedX, int speedY, Texture* texture) : SceneElement(posX, posY, texture) {
	m_speedX = speedX;
	m_speedY = speedY;
	m_lastMov = DOWN;
	
	m_frame = 0;
	m_timeSinceLastMov = 0;

	m_sceneElements = nullptr;

	m_walkingEffect = NULL;

	// Set standard alpha blending
	//m_texture->setBlendMode(SDL_BLENDMODE_BLEND);
}

Character::~Character() {
	// Free the sound effect
	if (m_walkingEffect != NULL) {
		Mix_FreeChunk(m_walkingEffect);
		m_walkingEffect = NULL;
	}
}

void Character::display() {
	if (m_texture != NULL) {
		m_texture->render(m_posX, m_posY, m_lastMov, m_frame);
	}
}

void Character::move(int direction) {
	Uint32 time = SDL_GetTicks();
	int newX = m_posX;
	int newY = m_posY;
	int newMov = m_lastMov;

	switch (direction) {
	case UP:
		newY -= m_speedY;
		newMov = UP;
		break;

	case DOWN:
		newY += m_speedY;
		newMov = DOWN;
		break;

	case LEFT:
		newX -= m_speedX;
		newMov = LEFT;
		break;

	case RIGHT:
		newX += m_speedX;
		newMov = RIGHT;
		break;
	}

	if (!checkCollision(newX, newY)) {
		m_posX = newX;
		m_posY = newY;
		m_lastMov = newMov;

		if (direction == m_lastMov) {
			if (time - m_timeSinceLastMov >= 500) {
				m_frame++;
				m_frame %= m_animationNb;
				m_timeSinceLastMov = time;
			}
		}
		else {
			m_frame = 0;
			m_timeSinceLastMov = time;
		}

		if (m_walkingEffect != NULL) {
			Mix_PlayChannel(-1, m_walkingEffect, 0);
		}
	}
}

void Character::move(int x, int y) {
	if (!checkCollision(x, y)) {
		m_posX = x;
		m_posY = y;
		m_lastMov = DOWN;
		m_frame = 0;
		m_timeSinceLastMov = SDL_GetTicks();
	}
}

void Character::setWalkingEffect(std::string path) {
	m_walkingEffect = Mix_LoadWAV(path.c_str());
	if (m_walkingEffect == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}