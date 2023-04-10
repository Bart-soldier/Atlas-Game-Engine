#include "Texture.hpp"

Texture::Texture(GraphicsEngine* graphicsEngine, TTF_Font* font, std::string text, SDL_Color color) {
	// Initialize
	reset();

	m_graphicsEngine = graphicsEngine;
	m_font = font;
	m_spriteColumnNb = 1;
	m_spriteLineNb = 1;
	loadFromRenderedText(text, color);
}

Texture::Texture(GraphicsEngine* graphicsEngine, std::string path, int spriteColumnNb, int spriteLineNb) {
	// Initialize
	reset();

	m_graphicsEngine = graphicsEngine;
	m_spriteColumnNb = spriteColumnNb;
	m_spriteLineNb = spriteLineNb;
	loadFromFile(path);
}

Texture::~Texture() {
	// Deallocate
	free();

	// Free font if it exists
	if (m_font != NULL) {
		// Free font
		TTF_CloseFont(m_font);
		m_font = NULL;
	}
}

void Texture::free() {
	//Free texture if it exists
	if (m_texture != NULL) {
		SDL_DestroyTexture(m_texture);
		reset();
		m_spriteClips.clear();
	}
}

void Texture::reset() {
	// Initialize
	m_texture = NULL;
	m_width = 0;
	m_height = 0;
	m_alpha = 255;
}

void Texture::intializeSpriteClips() {
	//m_spriteClips[m_directionNb * m_animationNb];

	m_objWidth = m_width / m_spriteColumnNb;
	m_objHeight = m_height / m_spriteLineNb;
	SDL_Rect spriteClip;

	for (int y = 0; y < m_spriteLineNb; y++) {
		for (int x = 0; x < m_spriteColumnNb; x++) {
			spriteClip.x = x * m_objWidth;
			spriteClip.y = y * m_objHeight;
			spriteClip.w = m_objWidth;
			spriteClip.h = m_objHeight;
			m_spriteClips.push_back(spriteClip);
		}
	}

	// Free unused vector space
	m_spriteClips.shrink_to_fit();
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
		m_width = loadedSurface->w;
		m_height = loadedSurface->h;
		if (m_width < TILESIZE) m_width = TILESIZE;
		if (m_height < TILESIZE) m_height = TILESIZE;

		// Resize surface
		SDL_Rect resizedRect;
		resizedRect.x = 0;
		resizedRect.y = 0;
		resizedRect.w = m_width * TILEFACTOR;
		resizedRect.h = m_height * TILEFACTOR;

		SDL_Surface* resizedSurface = SDL_CreateRGBSurface(
			loadedSurface->flags,
			resizedRect.w,
			resizedRect.h,
			loadedSurface->format->BitsPerPixel,
			loadedSurface->format->Rmask,
			loadedSurface->format->Gmask,
			loadedSurface->format->Bmask,
			loadedSurface->format->Amask);

		SDL_BlitScaled(loadedSurface, NULL, resizedSurface, &resizedRect);

		// Color key image
		SDL_SetColorKey(resizedSurface, SDL_TRUE, SDL_MapRGB(resizedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = m_graphicsEngine->createTexture(resizedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			return false;
		}
		else {
			// Get image dimensions
			m_width = resizedSurface->w;
			m_height = resizedSurface->h;
		}

		// Get rid of old loaded surfaces
		SDL_FreeSurface(loadedSurface);
		SDL_FreeSurface(resizedSurface);
	}

	// Return success
	m_texture = newTexture;

	intializeSpriteClips();

	return true;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
	// Get rid of preexisting texture
	free();

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, textureText.c_str(), textColor);
	if (textSurface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	else {
		// Create texture from surface pixels
		m_texture = m_graphicsEngine->createTexture(textSurface);
		if (m_texture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else {
			//Get image dimensions
			m_width = textSurface->w;
			m_height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	intializeSpriteClips();

	// Return success
	return true;
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

void Texture::render(int x, int y, int width, int height, int spriteLineIndex, int spriteColumnIndex, bool toCamera) {
	int newX = x;
	int newY = y;

	// Depth perspective
	if (m_objWidth > width) newX -= (m_objWidth - width) / 2;
	if (m_objHeight > height) newY -= (m_objHeight - height);

	m_graphicsEngine->render(m_texture, newX, newY, m_objWidth, m_objHeight,
		&m_spriteClips.at((spriteLineIndex * m_spriteColumnNb) + spriteColumnIndex), toCamera);
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

int Texture::getSpriteLineNb() {
	return m_spriteLineNb;
}

int Texture::getSpriteColumnNb() {
	return m_spriteColumnNb;
}