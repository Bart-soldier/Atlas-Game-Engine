#pragma once
#include "Object.hpp"

class Wall : public Object {
	public:
		Wall(int posX, int posY, Texture* texture = nullptr, int textureColumn = 0, int textureLine = 0);
};

