#include "SceneElement.hpp"

SceneElement::SceneElement(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path) {
	m_posX = posX;
	m_posY = posY;
	m_texture = new Texture(graphicsEngine, path);
}

SceneElement::~SceneElement() {
	m_texture->free();
}

void SceneElement::display() {
	m_texture->render(m_posX, m_posY);
}