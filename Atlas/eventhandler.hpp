#pragma once
#include <SDL.h>
#include "Player.hpp"

class EventHandler {
	private:
		Player* m_player;

	public:
		EventHandler(Player* player);
		bool handleEvent();
};

