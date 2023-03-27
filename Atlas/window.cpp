#include "window.hpp"

Window::Window(int width, int height) {
	m_width = width;
	m_height = height;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		//Create window
		m_window = SDL_CreateWindow("Atlas Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
		if(m_window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else {
			// Initialize renderer
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
			}
		}
	}
}

void Window::close() {
	// Destroy window    
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = NULL;
	m_window = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Window::loadTexture(std::string path) {
	SDL_Texture* m_optimizedTexture = NULL;
	SDL_Surface* m_loadedSurface = IMG_Load(path.c_str());

	if (m_loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Convert surface to screen format to optimize
		m_optimizedTexture = SDL_CreateTextureFromSurface(m_renderer, m_loadedSurface);
		if (m_optimizedTexture == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(m_loadedSurface);
	}

	return m_optimizedTexture;
}

void Window::unloadTexture(SDL_Texture* texture) {
	// Deallocate texture
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Window::updateWindow(SDL_Texture* texture) {
	// Clear screen
	SDL_RenderClear(m_renderer);

	// Render texture to screen
	SDL_RenderCopy(m_renderer, texture, NULL, NULL);

	//Update screen
	SDL_RenderPresent(m_renderer);
}
/*
void Window::updateWindow(SDL_Texture* texture, int x, int y, int width, int height) {
	//Apply the image stretched
	SDL_Rect m_rect;
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = width;
	m_rect.h = height;
	SDL_BlitScaled(surface, NULL, m_surface, &m_rect);

	//Update the surface
	SDL_UpdateWindowSurface(m_window);
}*/

SDL_Window* Window::getWindow() {
	return m_window;
}

bool Window::getExitStatus() {
	return m_exitStatus;
}

void Window::setExitStatus(bool exitStatus) {
	m_exitStatus = exitStatus;
}