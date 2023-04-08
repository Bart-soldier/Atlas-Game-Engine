#include "Scene.hpp"

Scene::Scene(GraphicsEngine* graphicsEngine) {
	m_graphicsEngine = graphicsEngine;
	m_width = 0;
	m_height = 0;
	m_player = nullptr;
	m_theme = NULL;
	m_entryX = 0;
	m_entryY = 0;
}

Scene::Scene(GraphicsEngine* graphicsEngine, int width, int height) {
	m_graphicsEngine = graphicsEngine;
	m_width = width;
	m_height = height;
	m_player = nullptr;
	m_theme = NULL;
	m_entryX = 0;
	m_entryY = 0;
}

Scene::~Scene() {
	// Free the music
	if (m_theme != NULL) {
		Mix_FreeMusic(m_theme);
		m_theme = NULL;
	}
}

void Scene::initializeSceneElements() {
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			m_sceneElements.push_back(std::make_pair(nullptr, nullptr));
		}
	}

	// Free unused vector space
	m_sceneElements.shrink_to_fit();
}

std::pair<SceneElement*, SceneElement*> Scene::getSceneElement(int x, int y) {
	return m_sceneElements.at(y * m_width + x);
}

void Scene::setSceneElementBackground(int x, int y, SceneElement* background) {
	m_sceneElements.at(y * m_width + x).first = background;
}

void Scene::setSceneElementForeground(int x, int y, SceneElement* foreground) {
	m_sceneElements.at(y * m_width + x).second = foreground;
}

void Scene::addPlayer(Player* player) {
	m_player = player;
	m_player->setSceneElements(&m_sceneElements, m_width);
	m_player->setPos(m_entryX, m_entryY);
}

void Scene::testLevel() {
	m_width = 10;
	m_height = 20;

	initializeSceneElements();

	Texture* sand = new Texture(m_graphicsEngine, "resources/images/Sand.png");
	Texture* tomb = new Texture(m_graphicsEngine, "resources/images/Tomb.png", 3, 4);

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			if (y == 0 || y == 1 || y == 2) {
				if (x == 0) setSceneElementForeground(x, y, new Wall(x, y, tomb, y, 0));
				else if(x == m_width - 1) setSceneElementForeground(x, y, new Wall(x, y, tomb, y, 2));
				else setSceneElementForeground(x, y, new Wall(x, y, tomb, y, 1));
			}
			else if (y == m_height - 1) {
				if (x == 0) setSceneElementForeground(x, y, new Wall(x, y, tomb, 3, 0));
				else if (x == m_width - 1) setSceneElementForeground(x, y, new Wall(x, y, tomb, 3, 2));
				else setSceneElementForeground(x, y, new Wall(x, y, tomb, 3, 1));
			}
			else if (x == 0) setSceneElementForeground(x, y, new Wall(x, y, tomb, 1, 0));
			else if (x == m_width - 1) setSceneElementForeground(x, y, new Wall(x, y, tomb, 1, 2));
			else setSceneElementBackground(x, y, new Environment(x, y, sand));
		}
	}

	int x = 4;
	int y = 4;
	Wall* ark = new Wall(x, y, new Texture(m_graphicsEngine, "resources/images/ArkCovenant.png"));
	setSceneElementForeground(x, y, ark);
	setSceneElementForeground(x + 1, y, ark);

	m_entryX = (m_width - 1) * TILESIZE * TILEFACTOR / 2;
	m_entryY = (m_height - 3) * TILESIZE * TILEFACTOR;
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

void Scene::setTheme(std::string path) {
	// Load music
	m_theme = Mix_LoadMUS(path.c_str());
	if (m_theme == NULL) {
		printf("Failed to load theme! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Scene::playTheme() {
	// Play the music
	if (m_theme == NULL) {
		printf("No music to play!");
	}
	else Mix_PlayMusic(m_theme, -1);
}