#include "Character.hpp"

Character::Character(int posX, int posY, Texture* texture) : SceneElement(posX, posY, texture) {
	m_speed = 2 * (TILESIZE * TILEFACTOR) / (FRAME_RATE);
	m_speedX = 0;
	m_speedY = 0;
	m_isRunning = false;
	m_direction = SOUTH;

	// Set feet level hitbox
	updateHitBox();
	m_hitBox.w = static_cast<int>(3 * m_width / 4);
	m_hitBox.h = static_cast<int>(m_height / 4);

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
		m_timeSinceLastFrame = SDL_GetTicks();
		m_direction = newDirection;
	}

	if (m_speedX == 0 && m_speedY == 0) {
		if (m_frame % 2 != 0) m_frame -= m_frame % 2;
	}
}

void Character::updateHitBox() {
	m_hitBox.x = m_posX + m_width / 8;
	m_hitBox.y = m_posY + m_height / 4;
}

void Character::display() {
	if (m_texture != NULL) {
		m_texture->render(m_posX, m_posY, m_direction, m_frame);

		// Set feet level corresponding tile
		int tile_x = m_hitBox.x / (TILESIZE * TILEFACTOR);
		int tile_y = m_hitBox.y / (TILESIZE * TILEFACTOR);

		// Get all neighbors
		std::vector<SceneElement*> neighbors = m_scene->getNeighborForegroundElements(tile_x, tile_y);

		for (auto element = neighbors.begin(); element != neighbors.end(); ++element) {
			if ((*element) != nullptr) {
				//printf("Their : x = %d", (*element)->getPosY());
				if ((*element)->getPosY() > m_posY) {
					//printf("true\n");
					(*element)->display();
				}
			}
		}
	}
}

SceneElement* Character::checkCollision(int posX, int posY) {
	// Get hypothetical hitbox
	int e_x = (posX + m_width / 8);
	int e_y = (posY + m_height / 4);
	SDL_Rect hitBox = m_hitBox;
	hitBox.x = e_x;
	hitBox.y = e_y;
	hitBox.w = m_hitBox.w;
	hitBox.h = m_hitBox.h;

	// Set feet level corresponding tile
	int tile_x = e_x / (TILESIZE * TILEFACTOR);
	int tile_y = e_y / (TILESIZE * TILEFACTOR);

	// Get all neighbors of correponding tile
	std::vector<SceneElement*> neighbors = m_scene->getNeighborForegroundElements(tile_x, tile_y);

	for (auto element = neighbors.begin(); element != neighbors.end(); ++element) {
		if ((*element) != nullptr) {
			if (GameplayEngine::checkCollision(hitBox, (*element)->getHitBox())) {
				return *element;
			}
		}
	}

	return nullptr;
}

void Character::handleCollision(SceneElement* element) {
	/*int e_x = element->getPosX();
	int e_y = element->getPosY();
	int e_w = element->getWidth();
	int e_h = element->getHeight();

	//printf("Me : x = %d, y = %d, w = %d, h = %d\n", m_hitBox.x, m_hitBox.y, m_hitBox.w, m_hitBox.h);
	//printf("Him : x = %d, y = %d, w = %d, h = %d\n", e_x, e_y, e_w, e_h);

	if ((m_hitBox.y <= e_y && e_y < m_hitBox.y + m_hitBox.h) || (e_y <= m_hitBox.y && m_hitBox.y < e_y + e_h)) {
		if (m_hitBox.x < e_x) {
			m_posX = e_x - m_hitBox.w - (m_width - m_hitBox.w) / 2;
		}
		else {
			m_posX = e_x + m_hitBox.w + (m_width - m_hitBox.w) / 2;
		}
	}

	//m_hitBox.x = m_posX + m_width / 8;
	//m_hitBox.y = m_posY + m_height / 4;
	//m_hitBox.w = static_cast<int>(3 * m_width / 4);
	//m_hitBox.h = static_cast<int>(m_height / 4);

	if ((m_hitBox.x <= e_x && e_x < m_hitBox.x + m_hitBox.w) || (e_x <= m_hitBox.x && m_hitBox.x < e_x + e_w)) {
		if (m_hitBox.y < e_y) {
			m_posY = e_y - m_hitBox.h;
		}
		else {
			m_posY = e_y + m_hitBox.h;
		}
	}


	updateHitBox();

	Uint32 time = SDL_GetTicks();

	if (time - m_timeSinceLastFrame >= 200) {
		m_frame++;
		m_frame %= m_texture->getSpriteColumnNb();
		m_timeSinceLastFrame = time;
	}

	if (m_walkingEffect != NULL) {
		Mix_PlayChannel(-1, m_walkingEffect, 0);
	}*/
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
		m_speed *= 30;
		m_speedX *= 30;
		m_speedY *= 30;
	}
	else {
		m_speed /= 30;
		m_speedX /= 30;
		m_speedY /= 30;
	}

	m_isRunning = !m_isRunning;
}

void Character::move() {
	if (m_speedX != 0 || m_speedY != 0) {
		int newX = static_cast<int>(m_posX + m_speedX);
		int newY = static_cast<int>(m_posY + m_speedY);

		// Check collision at feet level
		SceneElement* collision_e = checkCollision(newX, newY);
		if (collision_e == nullptr) {
			m_posX = newX;
			m_posY = newY;
			updateHitBox();

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