#pragma once
#include "SceneElement.hpp"

class Object : public SceneElement {
	private:
		int m_textureColumn;
		int m_textureLine;

	public:
		Object(int posX, int posY, Texture* texture = nullptr, int textureColumn = 0, int textureLine = 0);
		void display() override;
};

