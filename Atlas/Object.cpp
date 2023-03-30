#include "Object.hpp"

Object::Object(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path)
	: SceneElement(posX, posY) {
	createTexture(graphicsEngine, path);
}

void Object::display() {
	m_texture->render(m_posX, m_posY);
}