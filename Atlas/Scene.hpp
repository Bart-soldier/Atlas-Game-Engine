#pragma once

#include "GraphicsEngine.hpp"
#include "Wall.hpp"
#include "Environment.hpp"
#include "Player.hpp"

class Scene {
	private:
		GraphicsEngine* m_graphicsEngine;
		int m_width;
		int m_height;

		std::vector<std::pair<Environment*, Object*>> m_sceneElements;
		Player* m_player;

	public:
		Scene(GraphicsEngine* graphicsEngine, int width, int height);
		void addPlayer(Player* player);
		void testLevel();
		void update();
		void display();
};

