#include "Relic.hpp"

Relic::Relic(int posX, int posY, Texture* texture, int spriteColumnIndex, int spriteLineIndex) :
	Object(posX, posY, texture, spriteColumnIndex, spriteLineIndex) {
	m_isInteractable = true;
}

std::pair<int, int> Relic::interact() {
	return std::make_pair(ADD_INVENTORY, -1);
}