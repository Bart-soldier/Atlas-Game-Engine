#pragma once
#include "Texture.hpp"

class SceneElement {
	private:
		int m_x;
		int m_y;
		Texture* m_texture = NULL;

	public:
		SceneElement(GraphicsEngine* graphicsEngine, int x, int y, std::string path);
		~SceneElement();

		void display();
};