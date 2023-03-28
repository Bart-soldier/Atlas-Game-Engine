#pragma once
#include "Texture.hpp"

class SceneElement {
	protected:
		int m_posX;
		int m_posY;
		Texture* m_texture = NULL;

	public:
		SceneElement(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path);
		~SceneElement();

		void display();
};