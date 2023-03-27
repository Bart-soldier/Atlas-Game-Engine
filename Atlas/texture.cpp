#include "Texture.hpp"

Texture::Texture(GraphicsEngine* graphicsEngine) {
	// Initialize
	m_graphicsEngine = graphicsEngine;
	m_texture = NULL;
	m_width = 0;
	m_height = 0;
}

Texture::Texture(GraphicsEngine* graphicsEngine, std::string path) {
	// Initialize
	m_graphicsEngine = graphicsEngine;
	m_width = 0;
	m_height = 0;
	loadFromFile(path);
}

Texture::~Texture() {
	// Deallocate
	free();
}

bool Texture::loadFromFile(std::string path) {
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}
	else {
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = m_graphicsEngine->createTexture(loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			return false;
		}
		else {
			// Get image dimensions
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	m_texture = newTexture;
	return true;
}

void Texture::free() {
	//Free texture if it exists
	if (m_texture != NULL) {
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}

void Texture::render(int x, int y) {
	m_graphicsEngine->render(m_texture, x, y, m_width, m_height);
}

int Texture::getWidth() {
	return m_width;
}

int Texture::getHeight() {
	return m_height;
}