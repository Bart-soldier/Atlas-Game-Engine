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

		std::vector<std::pair<SceneElement*, SceneElement*>> m_sceneElements;
		Player* m_player;

		Mix_Music* m_theme;

	public:
		Scene(GraphicsEngine* graphicsEngine, int width, int height);
		~Scene();
		void addPlayer(Player* player);
		void testLevel();
		void update();
		void display();
		void setTheme(std::string path);
		void playTheme();
};

