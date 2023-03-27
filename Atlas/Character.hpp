#pragma once
#include "SceneElement.hpp"

class Character : public SceneElement {
	public:
		Character(GraphicsEngine* graphicsEngine, int x, int y, std::string path);
};