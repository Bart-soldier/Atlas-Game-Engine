#include "GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine(int width, int height) {
	m_window = NULL;
	m_renderer = NULL;
	m_width = width;
	m_height = height;
	m_camera = NULL;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		//Create window
		m_window = SDL_CreateWindow("Atlas Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			m_width, m_height, SDL_WINDOW_SHOWN);
		if(m_window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else {
			// Initialize renderer with vsync
			//m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
			if (m_renderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else {
				// Initialize renderer color
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				}
			}
		}
	}
}

GraphicsEngine::~GraphicsEngine() {
	// Destroy window    
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = NULL;
	m_window = NULL;

	// Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* GraphicsEngine::createTexture(SDL_Surface* surface) {
	return SDL_CreateTextureFromSurface(m_renderer, surface);
}

void GraphicsEngine::render(SDL_Texture* texture, int x, int y, int width, int height, SDL_Rect* clip, bool toCamera) {
	// Set rendering space and scale to render to screen or camera
	SDL_Rect renderQuad = { x, y, width, height };
	if (m_camera != NULL && toCamera) renderQuad = { x - m_camera->getPosX(), y - m_camera->getPosY(), m_camera->getWidth(),
		m_camera->getHeight() };

	// Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(m_renderer, texture, clip, &renderQuad);
}

void GraphicsEngine::clearScreen() {
	// Clear screen
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
}

void GraphicsEngine::updateScreen() {
	// Update screen
	SDL_RenderPresent(m_renderer);
}

void GraphicsEngine::drawRectangle() {
	// Clear screen
	SDL_RenderClear(m_renderer);

	//Render red filled quad
	SDL_Rect m_fillRect = { m_width / 4, m_height / 4, m_width / 2, m_height / 2 };
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(m_renderer, &m_fillRect);

	//Render green outlined quad
	SDL_Rect m_outlineRect = { m_width / 6, m_height / 6, m_width * 2 / 3, m_height * 2 / 3 };
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(m_renderer, &m_outlineRect);

	//Draw blue horizontal line
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(m_renderer, 0, m_height / 2, m_width, m_height / 2);

	//Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0x00, 0xFF);
	for(int i = 0; i < m_height; i += 4) {
		SDL_RenderDrawPoint(m_renderer, m_width / 2, i);
	}

	//Update screen
	SDL_RenderPresent(m_renderer);

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

int GraphicsEngine::getWidth() {
	return m_width;
}

int GraphicsEngine::getHeight() {
	return m_height;
}

bool GraphicsEngine::getExitStatus() {
	return m_exitStatus;
}

void GraphicsEngine::setExitStatus(bool exitStatus) {
	m_exitStatus = exitStatus;
}

void GraphicsEngine::setCamera(Camera* camera) {
	m_camera = camera;
}