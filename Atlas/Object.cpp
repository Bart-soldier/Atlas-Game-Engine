#include "Object.hpp"

Object::Object(int posX, int posY, Texture* texture, int textureColumn, int textureLine) : SceneElement(posX, posY, texture) {
	m_textureColumn = textureColumn;
	m_textureLine = textureLine;
}

void Object::display() {
	m_texture->render(m_posX, m_posY, m_textureColumn, m_textureLine);
}