#pragma once
#include "Object.hpp"

class Relic : public Object {
	public:
		Relic(int posX, int posY, Texture* texture = nullptr, int spriteColumnIndex = 0, int spriteLineIndex = 0);

		std::pair<int, int> interact() override;
};

