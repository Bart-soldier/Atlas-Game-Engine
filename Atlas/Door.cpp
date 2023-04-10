#include "Door.hpp"

Door::Door(int posX, int posY, int toSceneIndex, Texture* texture, int spriteColumnIndex, int spriteLineIndex) :
	Object(posX, posY, texture, spriteColumnIndex, spriteLineIndex) {
	m_toSceneIndex = toSceneIndex;
	m_isInteractable = true;
}

void Door::activate() {
}

int Door::getToSceneIndex() {
	return m_toSceneIndex;
}