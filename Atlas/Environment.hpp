#pragma once
#include "SceneElement.hpp"

class Environment : public SceneElement {
	public:
		Environment(GraphicsEngine* graphicsEngine, int x, int y, std::string path);
};