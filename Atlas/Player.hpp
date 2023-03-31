#pragma once
#include "Character.hpp"

class Player : public Character {
	public:
		Player(int posX, int posY, int speedX, int speedY, Texture* texture = nullptr);
};

