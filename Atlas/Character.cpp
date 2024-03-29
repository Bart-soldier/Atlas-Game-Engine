#include "Character.hpp"

Character::Character(int posX, int posY, Texture* texture) : SceneElement(posX, posY, texture) {
	m_height = m_height / 4;
	m_width = 3 * m_width / 4;

	m_speed = 2 * (TILESIZE * TILEFACTOR) / (FRAME_RATE);
	m_speedX = 0;
	m_speedY = 0;
	m_isRunning = false;
	m_direction = SOUTH;

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
		m_timeSinceLastFrame = SDL_GetTicks();
		m_direction = newDirection;
	}

	if (m_speedX == 0 && m_speedY == 0) {
		if (m_frame % 2 != 0) m_frame -= m_frame % 2;
	}
}

void Character::display() {
	if (m_texture != NULL) m_texture->render(m_posX, m_posY, m_width, m_height, m_direction, m_frame);
}

SceneElement* Character::checkCollision(int posX, int posY, std::vector<SceneElement*> neighbors) {
	SDL_Rect e1_hb = { posX, posY, m_width, m_height };

	for (auto element = neighbors.begin(); element != neighbors.end(); ++element) {
		if ((*element) != nullptr) {
			SDL_Rect e2_hb = { (*element)->getPosX(), (*element)->getPosY(), (*element)->getWidth(), (*element)->getHeight() };
			
			if (((e2_hb.x <= e1_hb.x && e1_hb.x < e2_hb.x + e2_hb.w) || (e1_hb.x <= e2_hb.x && e2_hb.x < e1_hb.x + e1_hb.w))
				&& ((e2_hb.y <= e1_hb.y && e1_hb.y < e2_hb.y + e2_hb.h) || (e1_hb.y <= e2_hb.y && e2_hb.y < e1_hb.y + e1_hb.h))) 
				return *element;
		}
	}

	return nullptr;
}

void Character::handleCollision(SceneElement* element) {
	int e_x = element->getPosX();
	int e_y = element->getPosY();
	int e_w = element->getWidth();
	int e_h = element->getHeight();

	if ((m_posY <= e_y && e_y < m_posY + m_height) || (e_y <= m_posY && m_posY < e_y + e_h)) {
		m_posX = (m_posX < e_x) ? e_x - m_width : e_x + e_w;
	}

	if ((m_posX <= e_x && e_x < m_posX + m_width) || (e_x <= m_posX && m_posX < e_x + e_w)) {
		m_posY = (m_posY < e_y) ? e_y - m_height : e_y + e_h;
	}
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

void Character::move(std::vector<SceneElement*> neighbors) {
	bool moved = false;

	if (m_speedX != 0) {
		int newX = static_cast<int>(m_posX + m_speedX);
		SceneElement* collision_e = checkCollision(newX, m_posY, neighbors);

		if (collision_e == nullptr) {
			m_posX = newX;
			moved = true;
		}
		else handleCollision(collision_e);
	}

	if (m_speedY != 0) {
		int newY = static_cast<int>(m_posY + m_speedY);
		SceneElement* collision_e = checkCollision(m_posX, newY, neighbors);

		if (collision_e == nullptr) {
			m_posY = newY;
			moved = true;
		}
		else handleCollision(collision_e);
	}

	if (moved) {
		Uint32 time = SDL_GetTicks();

		if (time - m_timeSinceLastFrame >= 200) {
			m_frame++;
			m_frame %= m_texture->getSpriteColumnNb();
			m_timeSinceLastFrame = time;
		}

		if (m_walkingEffect != NULL) {
			Mix_PlayChannel(-1, m_walkingEffect, 0);
		}
	}
	else if (m_frame % 2 != 0) m_frame -= m_frame % 2;
}

void Character::setWalkingEffect(std::string path) {
	m_walkingEffect = Mix_LoadWAV(path.c_str());
	if (m_walkingEffect == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}