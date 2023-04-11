#pragma once
#include "Object.hpp"

class Door : public Object {
	private:
		int m_destination;

	public:
		Door(int posX, int posY, int destination, Texture* texture = nullptr, int spriteColumnIndex = 0, int spriteLineIndex = 0);

		std::pair<int, int> interact() override;
};
