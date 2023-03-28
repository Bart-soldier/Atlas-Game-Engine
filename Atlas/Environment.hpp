#pragma once
#include "SceneElement.hpp"

class Environment : public SceneElement {
	public:
		Environment(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path);

		void display();
};