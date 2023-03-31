#include "Scene.hpp"

Scene::Scene(GraphicsEngine* graphicsEngine, int width, int height) {
	m_graphicsEngine = graphicsEngine;
	m_width = width;
	m_height = height;
}

void Scene::testLevel() {
	Texture* floor = new Texture(m_graphicsEngine, "resources/images/floor.png");
	Texture* wall = new Texture(m_graphicsEngine, "resources/images/wall.png");

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			if (x == 0 || x == m_height - 1 || y == 0 || y == m_width - 1) {
				m_sceneElements.push_back(std::make_pair(new Environment(x, y), new Wall(x, y)));
				m_sceneElements.back().first->setTexture(floor);
				m_sceneElements.back().second->setTexture(wall);
			}
			else {
				m_sceneElements.push_back(std::make_pair(new Environment(x, y), nullptr));
				m_sceneElements.back().first->setTexture(floor);
			}
		}
	}

	int x = 5;
	int y = 5;
	m_sceneElements.at(x * m_width + y).second = new Wall(x, y);
	m_sceneElements.at(x * m_width + y).second->setTexture(wall);

	// Free unused vector space
	m_sceneElements.shrink_to_fit();

	/*
	// Create scene elements
	m_sceneElements.push_back(new Environment(m_graphicsEngine, 0, 0, "resources/images/background.png"));
	//background->setTheme("resources/audio/theme.wav");
	//background->playTheme();

	Texture* wall = new Texture(m_graphicsEngine, "resources/images/wall.png");

	m_sceneElements.push_back(new Wall(m_graphicsEngine->getWidth() / 2, m_graphicsEngine->getHeight() / 2));
	m_sceneElements.back()->setTexture(wall);
	m_sceneElements.push_back(new Wall(3 * m_graphicsEngine->getWidth() / 4, 3 * m_graphicsEngine->getHeight() / 4));
	m_sceneElements.back()->setTexture(wall);
	m_sceneElements.push_back(new Wall(3 * m_graphicsEngine->getWidth() / 4, m_graphicsEngine->getHeight() / 4));
	m_sceneElements.back()->setTexture(wall);*/
}

void Scene::display() {
	// Render every scene element
	for (auto pair = m_sceneElements.begin(); pair != m_sceneElements.end(); ++pair) {
		if (pair->first != nullptr) {
			(pair->first)->display();
		}
		if (pair->second != nullptr) {
			(pair->second)->display();
		}
		//(*sceneElement)->display();
	}
}