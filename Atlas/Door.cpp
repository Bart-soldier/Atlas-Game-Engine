#include "Door.hpp"

Door::Door(int posX, int posY, int destination, Texture* texture, int spriteColumnIndex, int spriteLineIndex) :
	Object(posX, posY, texture, spriteColumnIndex, spriteLineIndex) {
	m_destination = destination;
	m_isInteractable = true;
}

std::pair<int, int> Door::interact() {
	return std::make_pair(CHANGE_SCENE, m_destination);
}