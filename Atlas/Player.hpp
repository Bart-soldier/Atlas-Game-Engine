#pragma once
#include "Character.hpp"
#include "Inventory.hpp"

class Player : public Character {
	private:
		Inventory* m_inventory;

	public:
		Player(int posX, int posY, Texture* texture = nullptr);

		void createInventory(Texture* texture, int space);
		bool addToInventory(Object* object);
		void display() override;
};

