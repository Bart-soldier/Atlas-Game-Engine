#include "window.hpp"

Window::Window() {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		//Create window
		m_window = SDL_CreateWindow("Atlas Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else {
			//Get window surface
			m_surface = SDL_GetWindowSurface(m_window);
		}
	}
}

void Window::close() {
	//Destroy window
	SDL_DestroyWindow(m_window);
	m_window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Surface* Window::loadSurface(std::string path) {
	//Load splash image
	SDL_Surface* m_surface = SDL_LoadBMP(path.c_str());
	if (m_surface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return m_surface;
}

void Window::unloadSurface(SDL_Surface* surface) {
	//Deallocate surface
	SDL_FreeSurface(surface);
	surface = NULL;
}

void Window::updateSurface(SDL_Surface* surface) {
	//Apply the image
	SDL_BlitSurface(surface, NULL, m_surface, NULL);

	//Update the surface
	SDL_UpdateWindowSurface(m_window);
}

SDL_Window* Window::getWindow() {
	return m_window;
}

SDL_Surface* Window::getSurface() {
	return m_surface;
}

bool Window::getExitStatus() {
	return m_exitStatus;
}

void Window::setExitStatus(bool exitStatus) {
	m_exitStatus = exitStatus;
}