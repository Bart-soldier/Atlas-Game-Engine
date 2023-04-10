#include "Relic.hpp"

Relic::Relic(int posX, int posY, Texture* texture, int spriteColumnIndex, int spriteLineIndex) :
	Object(posX, posY, texture, spriteColumnIndex, spriteLineIndex) {
	m_hitBox.h = m_height / 2;
}