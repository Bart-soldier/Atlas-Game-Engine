#pragma once
#include "SceneElement.hpp"

class Object : public SceneElement {
	public:
		Object(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path);

		void display();
};

