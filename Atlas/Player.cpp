#include "Player.hpp"

Player::Player(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path, int speedX, int speedY, int animationNb) :
	Character(graphicsEngine, posX, posY, path, speedX, speedY, animationNb) {
}

Player::Player(int posX, int posY, int speedX, int speedY) : Character(posX, posY, speedX, speedY) {
}