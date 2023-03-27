// Includes
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include "eventhandler.hpp"

int main(int argc, char* args[]) {
	// Create Window
	Window* m_window = new Window(640, 480);
	//Create EventHandler
	EventHandler* m_eventHandler = new EventHandler(m_window);

	if (m_window == NULL) {
		return EXIT_FAILURE;
	}

	// Main loop
	while (!m_window->getExitStatus()) {
		//Handle events on queue
		m_eventHandler->handleEvent();
	}

	m_window->close();

	return EXIT_SUCCESS;
}