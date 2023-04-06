#pragma once
#include "SceneElement.hpp"

class Environment : public SceneElement {
	public:
		Environment(int posX, int posY, Texture* texture = nullptr);
};