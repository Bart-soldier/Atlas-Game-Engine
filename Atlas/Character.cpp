#include "Character.hpp"

Character::Character(int posX, int posY, Texture* texture) : SceneElement(posX, posY, texture) {
	m_speed = 2 * (TILESIZE * TILEFACTOR) / (FRAME_RATE);
	m_speedX = 0;
	m_speedY = 0;
	m_isRunning = false;
	m_direction = SOUTH;

	m_scene = NULL;

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

SceneElement* Character::checkCollision(int posX, int posY) {
	// Set feet level variables
	int e_x = posX + 2 * TILEFACTOR;
	int e_w = m_width - 4 * TILEFACTOR;
	int e_h = TILESIZE * TILEFACTOR / 2;
	int e_y = posY + m_height - e_h;

	// Get corresponding tile
	int tile_x = e_x / (TILESIZE * TILEFACTOR);
	int tile_y = e_y / (TILESIZE * TILEFACTOR);

	std::vector<SceneElement*> neighbors = m_scene->getNeighborForegroundElements(tile_x, tile_y);

	for (auto element = neighbors.begin(); element != neighbors.end(); ++element) {
		if ((*element) != nullptr) {
			int e2_x = (*element)->getPosX();
			int e2_y = (*element)->getPosY();
			int e2_w = (*element)->getWidth();
			int e2_h = (*element)->getHeight();

			if (GameplayEngine::checkCollision(e_x, e_y, e_w, e_h, e2_x, e2_y, e2_w, e2_h)) {
				return *element;
			}
		}
	}

	return nullptr;
}

void Character::handleCollision(SceneElement* element) {
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
		SceneElement* collision_e = checkCollision(newX, newY);
		if (collision_e == nullptr) {
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
		else {
			handleCollision(collision_e);
		}
	}
}

void Character::addToScene(Scene* scene) {
	m_scene = scene;

	std::pair<int, int> entry = scene->getEntry();
	m_posX = entry.first;
	m_posY = entry.second;
}

void Character::setWalkingEffect(std::string path) {
	m_walkingEffect = Mix_LoadWAV(path.c_str());
	if (m_walkingEffect == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}