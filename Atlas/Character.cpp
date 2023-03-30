#include "Character.hpp"

Character::Character(GraphicsEngine* graphicsEngine, int x, int y, std::string path, int speedX, int speedY,
	int animationNb, int directionNb) : SceneElement(x, y) {
	createTexture(graphicsEngine, path, animationNb, directionNb);
	m_speedX = speedX;
	m_speedY = speedY;
	m_lastMov = DOWN;

	m_frame = 0;
	m_timeSinceLastMov = 0;
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
	m_texture->render(m_posX, m_posY, m_lastMov, m_frame);
}

void Character::move(int direction) {
	Uint32 time = SDL_GetTicks();

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

void Character::move(int x, int y) {
	m_posX = x;
	m_posY = y;
	m_lastMov = DOWN;
}

void Character::setWalkingEffect(std::string path) {
	m_walkingEffect = Mix_LoadWAV(path.c_str());
	if (m_walkingEffect == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}