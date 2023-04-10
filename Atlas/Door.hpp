#pragma once
#include "Object.hpp"

class Door : public Object {
	private:
		int m_toSceneIndex;

	public:
		Door(int posX, int posY, int toSceneIndex, Texture* texture = nullptr, int spriteColumnIndex = 0, int spriteLineIndex = 0);

		void activate() override;

		int getToSceneIndex();
};
