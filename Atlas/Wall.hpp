#pragma once
#include "Object.hpp"

class Wall : public Object {
	public:
		Wall(int posX, int posY, Texture* texture = nullptr, int spriteColumnIndex = 0, int spriteLineIndex = 0);
};

