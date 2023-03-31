#include "Environment.hpp"

Environment::Environment(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path)
	: SceneElement(posX, posY) {
	createTexture(graphicsEngine, path);
	m_theme = NULL;
}

Environment::Environment(int posX, int posY) : SceneElement(posX, posY) {
}

Environment::~Environment() {
	// Free the music
	if (m_theme != NULL) {
		Mix_FreeMusic(m_theme);
		m_theme = NULL;
	}
}

void Environment::display() {
	m_texture->render(m_posX, m_posY);
}

void Environment::setTheme(std::string path) {
	// Load music
	m_theme = Mix_LoadMUS(path.c_str());
	if (m_theme == NULL) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Environment::playTheme() {
	// Play the music
	if (m_theme == NULL) {
		printf("No music to play!");
	}
	else Mix_PlayMusic(m_theme, -1);
}