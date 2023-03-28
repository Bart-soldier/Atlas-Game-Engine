#include "Player.hpp"

Player::Player(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path, int speedX, int speedY) :
	Character(graphicsEngine, posX, posY, path, speedX, speedY) {
}
