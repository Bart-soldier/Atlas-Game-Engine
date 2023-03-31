#include "Object.hpp"

Object::Object(int posX, int posY, Texture* texture) : SceneElement(posX, posY, texture) {
}

void Object::display() {
	if (m_texture != NULL) {
		m_texture->render(m_posX, m_posY);
	}
}