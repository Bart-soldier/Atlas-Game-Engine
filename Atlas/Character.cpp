#include "Character.hpp"

Character::Character(int posX, int posY, Texture* texture) : SceneElement(posX, posY, texture) {
	m_speed = 2 * (TILESIZE * TILEFACTOR) / (FRAME_RATE);
	m_speedX = 0;
	m_speedY = 0;
	m_isRunning = false;
	m_direction = SOUTH;

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

void Character::checkDirection(int direction) {
	int newDirection = m_direction;

	if (m_speedY < 0) newDirection = NORTH;
	if (m_speedY > 0) newDirection = SOUTH;
	if (m_speedX < 0) newDirection = WEST;
	if (m_speedX > 0) newDirection = EAST;

	if (newDirection != m_direction) {
		m_frame = 0;
		m_timeSinceLastMov = SDL_GetTicks();
		m_direction = newDirection;
	}

	if (m_speedX == 0 && m_speedY == 0) {
		if (m_frame % 2 != 0) m_frame -= m_frame % 2;
	}
}

void Character::display() {
	if (m_texture != NULL) {
		m_texture->render(m_posX, m_posY, m_direction, m_frame);
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

void Character::startMovement(int direction) {
	switch (direction) {
	case NORTH:
		m_speedY -= m_speed;
		break;

	case SOUTH:
		m_speedY += m_speed;
		break;

	case WEST:
		m_speedX -= m_speed;
		break;

	case EAST:
		m_speedX += m_speed;
	}

	checkDirection(direction);
}

void Character::stopMovement(int direction) {
	switch (direction) {
	case NORTH:
		m_speedY += m_speed;
		break;

	case SOUTH:
		m_speedY -= m_speed;
		break;

	case WEST:
		m_speedX += m_speed;
		break;

	case EAST:
		m_speedX -= m_speed;
	}

	checkDirection(direction);
}

void Character::toggleRun() {
	if (!m_isRunning) {
		m_speed *= 3;
		m_speedX *= 3;
		m_speedY *= 3;
	}
	else {
		m_speed /= 3;
		m_speedX /= 3;
		m_speedY /= 3;
	}

	m_isRunning = !m_isRunning;
}

void Character::move() {
	if (m_speedX != 0 || m_speedY != 0) {
		int newX = m_posX + m_speedX;
		int newY = m_posY + m_speedY;

		// Check collision at feet level
		if (!checkCollision(newX, newY)) {
			m_posX = newX;
			m_posY = newY;

			Uint32 time = SDL_GetTicks();

			if (time - m_timeSinceLastMov >= 200) {
				m_frame++;
				m_frame %= m_animationNb;
				m_timeSinceLastMov = time;
			}

			if (m_walkingEffect != NULL) {
				Mix_PlayChannel(-1, m_walkingEffect, 0);
			}
		}
	}
}

/*
void Character::toggleRun() {
	if (!m_isRunning) m_speed *= 2;
	else m_speed /= 2;

	m_isRunning = !m_isRunning;
}*/

void Character::setWalkingEffect(std::string path) {
	m_walkingEffect = Mix_LoadWAV(path.c_str());
	if (m_walkingEffect == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}