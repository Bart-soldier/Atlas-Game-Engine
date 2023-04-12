#pragma once
#include "Character.hpp"
#include "Inventory.hpp"

class Player : public Character {
	private:
		Inventory* m_inventory;

	public:
		Player(int posX, int posY, Texture* texture = nullptr);

		void display() override;

		void setInventory(Texture* texture, int space);
		Inventory* getInventory();
};

