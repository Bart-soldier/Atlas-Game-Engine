#pragma once
#include "Texture.hpp"

class SceneElement {
	protected:
		int m_posX;
		int m_posY;
		int m_width;
		int m_height;
		Texture* m_texture;

		int m_directionNb;
		int m_animationNb;

	public:
		SceneElement(int posX, int posY, Texture* texture = nullptr);

		void setTexture(Texture* texture);
		virtual void display() = 0;
};