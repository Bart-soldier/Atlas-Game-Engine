#include "Object.hpp"

Object::Object(int posX, int posY, Texture* texture, int spriteColumnIndex, int spriteLineIndex) : SceneElement(posX, posY, texture) {
	m_spriteColumnIndex = spriteColumnIndex;
	m_spriteLineIndex = spriteLineIndex;
	m_height = TILESIZE * TILEFACTOR;
}

void Object::display() {
	m_texture->render(m_posX, m_posY, m_width, m_height, m_spriteLineIndex, m_spriteColumnIndex);
}

std::pair<int, int> Object::interact() {
	return std::make_pair(NONE, 0);
}