#include "Environment.hpp"

Environment::Environment(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path)
	: SceneElement(graphicsEngine, posX, posY, path) {
}

void Environment::display() {
	m_texture->render(m_posX, m_posY);
}