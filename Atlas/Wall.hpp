#pragma once
#include "Object.hpp"

class Wall : public Object {
	public:
		Wall(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path);
		Wall(int posX, int posY);
};

