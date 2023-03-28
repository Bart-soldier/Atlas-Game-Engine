#pragma once
#include "SceneElement.hpp"

const int ANIMATION_FRAMES = 2;

enum Directions {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	TOTAL_DIRECTIONS
};

class Character : public SceneElement {
	protected:
		int m_speedX;
		int m_speedY;
		int m_lastMov;
		int m_width;
		int m_height;

		// x, y, width, height
		SDL_Rect m_spriteClips[TOTAL_DIRECTIONS * ANIMATION_FRAMES];
		int m_frame = 0;

	public:
		Character(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path, int speedX, int speedY);
		void display();
		void move(int direction);
};