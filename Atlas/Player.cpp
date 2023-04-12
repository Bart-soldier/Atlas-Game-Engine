#include "Player.hpp"

Player::Player(int posX, int posY, Texture* texture) : Character(posX, posY, texture) {
	m_inventory = nullptr;
}

bool Player::addToInventory(Object* object) {
	return m_inventory->add(object);
}

void Player::createInventory(Texture* texture, int space) {
	m_inventory = new Inventory(texture, space);
}

void Player::display() {
	Character::display();

	if(m_inventory != nullptr) m_inventory->display();
}