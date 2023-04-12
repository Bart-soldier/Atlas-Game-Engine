#pragma once
#include "Relic.hpp"
#include "texture.hpp"

class Inventory {
	private:
		Texture* m_texture;
		std::vector<Object*> m_inventory;
		int m_space;
		int m_current;

		int m_posX;
		int m_posY;

	public:
		Inventory(Texture* texture, int space);
		void display();
		bool add(Object* object);
		void increment();
		void decrement();
};

