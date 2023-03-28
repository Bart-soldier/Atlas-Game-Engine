#pragma once
#include "Texture.hpp"

class SceneElement {
	protected:
		int m_posX;
		int m_posY;
		int m_width;
		int m_height;
		Texture* m_texture = NULL;

		int m_directionNb;
		int m_animationNb;

	public:
		SceneElement(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path, int animationNb = 1, int directionNb = 1);
		~SceneElement();

		virtual void display() = 0;
};