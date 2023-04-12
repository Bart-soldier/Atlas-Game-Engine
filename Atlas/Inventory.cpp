#include "Inventory.hpp"

Inventory::Inventory(Texture* texture, int space) {
	m_texture = texture;
	m_space = space;

	m_posX = (SCREEN_WIDTH - m_space * TILESIZE * TILEFACTOR) / 2;
	m_posY = SCREEN_HEIGHT - (3 * TILESIZE * TILEFACTOR) / 2;
}

void Inventory::display() {
	if (m_texture != NULL) {
		for (int i = 0; i < m_space; i++) {
			m_texture->render(m_posX + i * TILESIZE * TILEFACTOR, m_posY, TILESIZE * TILEFACTOR, TILESIZE * TILEFACTOR, 0, 0, false);
			if (i < m_inventory.size()) m_inventory.at(i)->display(m_posX, m_posY, TILESIZE * TILEFACTOR, TILESIZE * TILEFACTOR, false);
		}
	}
}

bool Inventory::add(Object* object) {
	if (m_inventory.size() < m_space) {
		m_inventory.push_back(object);
		return true;
	}
	
	return false;
}