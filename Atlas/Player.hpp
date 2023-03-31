#pragma once
#include "Character.hpp"

class Player : public Character {
	public:
		Player(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path, int speedX, int speedY, int animationNb);
		Player(int posX, int posY, int speedX, int speedY);
};

