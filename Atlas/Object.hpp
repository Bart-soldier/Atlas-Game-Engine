#pragma once
#include "SceneElement.hpp"

class Object : public SceneElement {
	public:
		Object(int posX, int posY, Texture* texture = nullptr);
};

