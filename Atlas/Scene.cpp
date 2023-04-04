#include "Scene.hpp"

Scene::Scene(GraphicsEngine* graphicsEngine, int width, int height) {
	m_graphicsEngine = graphicsEngine;
	m_width = width;
	m_height = height;
	m_player = nullptr;
}

void Scene::addPlayer(Player* player) {
	m_player = player;
	m_player->setSceneElements(&m_sceneElements, m_width);
}

void Scene::testLevel() {
	Texture* floor = new Texture(m_graphicsEngine, "resources/images/floor.png");
	Texture* wall = new Texture(m_graphicsEngine, "resources/images/wall.png");

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			if (x == 0 || x == m_height - 1 || y == 0 || y == m_width - 1) {
				m_sceneElements.push_back(std::make_pair(new Environment(x, y, floor), new Wall(x, y, wall)));
				//m_sceneElements.back().first->setTexture(floor);
				//m_sceneElements.back().second->setTexture(wall);
			}
			else {
				m_sceneElements.push_back(std::make_pair(new Environment(x, y, floor), nullptr));
			}
		}
	}

	int x = 6;
	int y = 5;
	m_sceneElements.at(y * m_width + x).second = new Wall(x, y);
	m_sceneElements.at(y * m_width + x).second->setTexture(wall);

	// Free unused vector space
	m_sceneElements.shrink_to_fit();
}

void Scene::update() {

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

	// Render player
	if (m_player != nullptr) {
		m_player->display();
	}
}