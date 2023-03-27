#include "SceneElement.hpp"

SceneElement::SceneElement(GraphicsEngine* graphicsEngine, int x, int y, std::string path) {
	m_x = x;
	m_y = y;
	m_texture = new Texture(graphicsEngine, path);
}

SceneElement::~SceneElement() {
	m_texture->free();
}

void SceneElement::display() {
	m_texture->render(m_x, m_y);
}