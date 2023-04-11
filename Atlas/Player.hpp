#pragma once
#include "Character.hpp"

class Player : public Character {
	private:

	public:
		Player(int posX, int posY, Texture* texture = nullptr);
};

