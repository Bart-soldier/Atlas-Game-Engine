#include "Player.hpp"

Player::Player(int posX, int posY, Texture* texture) : Character(posX, posY, texture) {
	m_inventory = nullptr;
}

void Player::display() {
	Character::display();

	if(m_inventory != nullptr) m_inventory->display();
}

void Player::setInventory(Texture* texture, int space) {
	m_inventory = new Inventory(texture, space);
}

Inventory* Player::getInventory() {
	return m_inventory;
}