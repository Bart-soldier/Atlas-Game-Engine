#include "Character.hpp"

Character::Character(int posX, int posY, int speedX, int speedY, Texture* texture) : SceneElement(posX, posY, texture) {
	m_speedX = speedX;
	m_speedY = speedY;
	m_lastMov = DOWN;

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

bool Character::checkCollision(int posX, int posY) {
	// Set feet level variables
	int feetHeight = TILESIZE * TILEFACTOR / 2;
	int feetY = posY + m_height - feetHeight;
	int feetX = posX + 2 * TILEFACTOR;
	int feetWidth = m_width - 4 * TILEFACTOR;

	// Get corresponding tile
	int tile_x = feetX / (TILESIZE * TILEFACTOR);
	int e_x = tile_x * TILESIZE * TILEFACTOR;
	int tile_y = feetY / (TILESIZE * TILEFACTOR);
	int e_y = tile_y * TILESIZE * TILEFACTOR;
	int e_w = e_x + TILESIZE * TILEFACTOR;
	int e_h = e_y + TILESIZE * TILEFACTOR;
	SceneElement* element = m_sceneElements->at(tile_y * m_sceneElementsWidth + tile_x).second;

	// Check destination
	if (element != nullptr) {
		handleCollision(element);
		return true;
	}

	// Check right tile
	if (feetX + feetWidth > e_w) {
		element = m_sceneElements->at(tile_y * m_sceneElementsWidth + tile_x + 1).second;
		if (element != nullptr) {
			handleCollision(element);
			return true;
		}
	}

	// Check bottom tile
	if (feetY + feetHeight > e_h) {
		element = m_sceneElements->at((tile_y + 1) * m_sceneElementsWidth + tile_x).second;
		if (element != nullptr) {
			handleCollision(element);
			return true;
		}
	}

	// Check bottom right tile
	if (feetX + feetWidth > e_w && feetY + feetHeight > e_h) {
		element = m_sceneElements->at((tile_y + 1) * m_sceneElementsWidth + tile_x + 1).second;
		if (element != nullptr) {
			handleCollision(element);
			return true;
		}
	}

	return false;
}

void Character::handleCollision(SceneElement* element) {
	m_frame = 0;
}

void Character::move(int direction) {
	Uint32 time = SDL_GetTicks();
	int newX = m_posX;
	int newY = m_posY;

	switch (direction) {
	case UP:
		newY -= m_speedY;
		m_lastMov = UP;
		break;

	case DOWN:
		newY += m_speedY;
		m_lastMov = DOWN;
		break;

	case LEFT:
		newX -= m_speedX;
		m_lastMov = LEFT;
		break;

	case RIGHT:
		newX += m_speedX;
		m_lastMov = RIGHT;
		break;
	}

	// Check collision at feet level
	if (!checkCollision(newX, newY)) {
		m_posX = newX;
		m_posY = newY;

		if (direction == m_lastMov) {
			if (time - m_timeSinceLastMov >= 200) {
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