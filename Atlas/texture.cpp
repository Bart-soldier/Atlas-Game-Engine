#include "Texture.hpp"

Texture::Texture(GraphicsEngine* graphicsEngine, int animationNb, int directionNb) {
	// Initialize
	m_graphicsEngine = graphicsEngine;
	m_texture = NULL;
	m_animationNb = animationNb;
	m_directionNb = directionNb;
	intializeSpriteClips();
}

Texture::Texture(GraphicsEngine* graphicsEngine, std::string path, int animationNb, int directionNb) {
	// Initialize
	m_graphicsEngine = graphicsEngine;
	loadFromFile(path);
	m_animationNb = animationNb;
	m_directionNb = directionNb;
	intializeSpriteClips();
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

void Texture::intializeSpriteClips() {
	m_spriteClips[m_directionNb * m_animationNb];

	int objWidth = m_width / m_animationNb;
	int objHeight = m_height / m_directionNb;

	for (int y = 0; y < m_directionNb; y++) {
		for (int x = 0; x < m_animationNb; x++) {
			m_spriteClips[(y * m_animationNb) + x].x = x * objWidth;
			m_spriteClips[(y * m_animationNb) + x].y = y * objHeight;
			m_spriteClips[(y * m_animationNb) + x].w = objWidth;
			m_spriteClips[(y * m_animationNb) + x].h = objHeight;
		}
	}
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	// Modulate texture
	SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blendMode) {
	// Set blending function
	SDL_SetTextureBlendMode(m_texture, blendMode);
}

void Texture::setAlpha(int alpha) {
	if (alpha < 0) alpha = 0;
	else if (alpha > 255) alpha = 255;
	m_alpha = alpha;

	// Modulate texture alpha
	SDL_SetTextureAlphaMod(m_texture, m_alpha);
}

void Texture::render(int x, int y, int lastMov, int frame) {
	m_graphicsEngine->render(m_texture, x, y, &m_spriteClips[(lastMov * m_animationNb) + frame]);
}

int Texture::getWidth() {
	return m_width;
}

int Texture::getHeight() {
	return m_height;
}

Uint8 Texture::getAplha() {
	return m_alpha;
}