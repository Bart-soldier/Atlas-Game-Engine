#include "Object.hpp"

Object::Object(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path)
	: SceneElement(posX, posY) {
	createTexture(graphicsEngine, path);
}

Object::Object(int posX, int posY) : SceneElement(posX, posY) {
}

void Object::display() {
	if (m_texture != NULL) {
		m_texture->render(m_posX, m_posY);
	}
}