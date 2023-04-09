#include "Object.hpp"

Object::Object(int posX, int posY, Texture* texture, int spriteColumnIndex, int spriteLineIndex) : SceneElement(posX, posY, texture) {
	m_spriteColumnIndex = spriteColumnIndex;
	m_spriteLineIndex = spriteLineIndex;
}

void Object::display() {
	m_texture->render(m_posX, m_posY, m_spriteColumnIndex, m_spriteLineIndex);
}