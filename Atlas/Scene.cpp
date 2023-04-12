#include "Scene.hpp"

Scene::Scene(GraphicsEngine* graphicsEngine) {
	m_graphicsEngine = graphicsEngine;
	m_width = 0;
	m_height = 0;
	m_theme = NULL;
	m_entry = std::make_pair(0, 0);
	m_isInterior = false;
}

Scene::Scene(GraphicsEngine* graphicsEngine, int width, int height) {
	m_graphicsEngine = graphicsEngine;
	m_width = width;
	m_height = height;
	m_theme = NULL;
	m_entry = std::make_pair(0, 0);
	m_isInterior = false;
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

Environment* Scene::getBackground(int x, int y) {
	if (x >= 0 && x < m_width && y >= 0 && y < m_height) return m_sceneElements.at(y * m_width + x).first;
	else return nullptr;
}

Object* Scene::getForeground(int x, int y) {
	if (x >= 0 && x < m_width && y >= 0 && y < m_height) return m_sceneElements.at(y * m_width + x).second;
	else return nullptr;
}

void Scene::removeBackground(int x, int y) {
	if (x >= 0 && x < m_width && y >= 0 && y < m_height) m_sceneElements.at(y * m_width + x).first = nullptr;
}

void Scene::removeForeground(int x, int y) {
	if (x >= 0 && x < m_width && y >= 0 && y < m_height) m_sceneElements.at(y * m_width + x).second = nullptr;
}

std::vector<SceneElement*> Scene::getNeighborForegroundElements(int e_x, int e_y) {
	std::vector<SceneElement*> neighborElements;

	for (int y = e_y - 1; y <= e_y + 1; y++) {
		for (int x = e_x - 1; x <= e_x + 1; x++) {
			if(x >= 0 && x < m_width && y >= 0 && y < m_height) neighborElements.push_back(getForeground(x, y));
		}
	}

	return neighborElements;
}

void Scene::setSceneElementBackground(int x, int y, Environment* background) {
	m_sceneElements.at(y * m_width + x).first = background;
}

void Scene::setSceneElementForeground(int x, int y, Object* foreground) {
	m_sceneElements.at(y * m_width + x).second = foreground;
}

void Scene::testLevel1() {
	m_width = 30;
	m_height = 20;
	m_isInterior = false;

	initializeSceneElements();

	Texture* grass = new Texture(m_graphicsEngine, "resources/images/Grass.png");
	Texture* darkGrass = new Texture(m_graphicsEngine, "resources/images/DarkGrass.png");

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			if (x == 0 || y == 0 || x == m_width - 1 || y == m_height - 1) setSceneElementForeground(x, y, new Wall(x, y, darkGrass));
			else setSceneElementBackground(x, y, new Environment(x, y, grass));
		}
	}

	Texture* tombWall = new Texture(m_graphicsEngine, "resources/images/TombExterior.png", 2);

	int x = m_width / 2;
	int y = 4;
	setSceneElementForeground(x, y, new Wall(x, y, tombWall));
	x++;
	setSceneElementForeground(x, y, new Door(x, y, 1, tombWall, 1));
	x++;
	setSceneElementForeground(x, y, new Wall(x, y, tombWall));

	m_entry.first = (m_width - 1) * TILESIZE * TILEFACTOR / 2;
	m_entry.second = (m_height - 3) * TILESIZE * TILEFACTOR;
}

void Scene::testLevel2() {
	m_width = 10;
	m_height = 20;
	m_isInterior = true;

	initializeSceneElements();

	Texture* sand = new Texture(m_graphicsEngine, "resources/images/Sand.png");
	Texture* tomb = new Texture(m_graphicsEngine, "resources/images/Tomb.png", 3, 4);

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			if (y == 0 || y == 1 || y == 2) {
				if (x == 0) setSceneElementForeground(x, y, new Wall(x, y, tomb, 0, y));
				else if(x == m_width - 1) setSceneElementForeground(x, y, new Wall(x, y, tomb, 2, y));
				else setSceneElementForeground(x, y, new Wall(x, y, tomb, 1, y));
			}
			else if (y == m_height - 1) {
				if (x == 0) setSceneElementForeground(x, y, new Wall(x, y, tomb, 0, 3));
				else if (x == m_width - 1) setSceneElementForeground(x, y, new Wall(x, y, tomb, 2, 3));
				else setSceneElementForeground(x, y, new Wall(x, y, tomb, 1, 3));
			}
			else if (x == 0) setSceneElementForeground(x, y, new Wall(x, y, tomb, 0, 1));
			else if (x == m_width - 1) setSceneElementForeground(x, y, new Wall(x, y, tomb, 2, 1));
			else setSceneElementBackground(x, y, new Environment(x, y, sand));
		}
	}

	// Ark
	int x = 4;
	int y = 4;
	Relic* ark = new Relic(x, y, new Texture(m_graphicsEngine, "resources/images/ArkCovenant.png"));
	setSceneElementForeground(x, y, ark);

	// Exit door
	x = 4;
	y = m_height - 1;
	Door* door = new Door(x, y, 0, new Texture(m_graphicsEngine, "resources/images/Door.png"));
	setSceneElementForeground(x, y, door);

	m_entry.first = (m_width - 1) * TILESIZE * TILEFACTOR / 2;
	m_entry.second = (m_height - 3) * TILESIZE * TILEFACTOR;
}

void Scene::update() {
}

void Scene::display() {
	// Render every scene element
	// Because of perspective, render background first, then foreground
	for (auto pair = m_sceneElements.begin(); pair != m_sceneElements.end(); ++pair) {
		if (pair->first != nullptr) {
			pair->first->display();
		}
		//(*sceneElement)->display();
	}
	for (auto pair = m_sceneElements.begin(); pair != m_sceneElements.end(); ++pair) {
		if (pair->second != nullptr) {
			pair->second->display();
		}
		//(*sceneElement)->display();
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

void Scene::stopTheme() {
	// Stop the music
	if (m_theme == NULL) {
		printf("No music to stop!");
	}
	else Mix_HaltMusic();
}

std::pair<int, int> Scene::getEntry() {
	return m_entry;
}

int Scene::getWidth() {
	return m_width;
}

int Scene::getHeight() {
	return m_height;
}

bool Scene::isInterior() {
	return m_isInterior;
}

void Scene::setEntry(std::pair<int, int> entry) {
	m_entry = entry;
}