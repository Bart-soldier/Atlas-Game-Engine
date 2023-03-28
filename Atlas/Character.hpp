#pragma once
#include "SceneElement.hpp"

enum Directions {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Character : public SceneElement {
	protected:
		int m_speedX;
		int m_speedY;

	public:
		Character(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path, int speedX, int speedY);
		void move(int direction);
};