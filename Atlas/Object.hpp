#pragma once
#include "SceneElement.hpp"

class Object : public SceneElement {
	private:
		int m_spriteColumnIndex;
		int m_spriteLineIndex;

	public:
		Object(int posX, int posY, Texture* texture = nullptr, int spriteColumnIndex = 0, int spriteLineIndex = 0);

		void display() override;
		void display(int posX, int posY, int width, int height, bool toCamera) override;
		virtual std::pair<int, int> interact();
};

