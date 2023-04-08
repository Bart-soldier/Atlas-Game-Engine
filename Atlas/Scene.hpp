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
		int m_entryX;
		int m_entryY;

		std::vector<std::pair<SceneElement*, SceneElement*>> m_sceneElements;
		Player* m_player;

		Mix_Music* m_theme;

		void initializeSceneElements();
		std::pair<SceneElement*, SceneElement*> getSceneElement(int x, int y);
		void setSceneElementBackground(int x, int y, SceneElement* background);
		void setSceneElementForeground(int x, int y, SceneElement* foreground);

	public:
		Scene(GraphicsEngine* graphicsEngine);
		Scene(GraphicsEngine* graphicsEngine, int width, int height);
		~Scene();
		void addPlayer(Player* player);
		void testLevel();
		void update();
		void display();
		void setTheme(std::string path);
		void playTheme();
};

