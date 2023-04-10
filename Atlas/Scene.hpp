#pragma once
#include "GraphicsEngine.hpp"
#include "Wall.hpp"
#include "Environment.hpp"
#include "Relic.hpp"

class Scene {
	private:
		GraphicsEngine* m_graphicsEngine;
		int m_width;
		int m_height;
		std::pair<int, int> m_entry;

		std::vector<std::pair<Environment*, Object*>> m_sceneElements;

		Mix_Music* m_theme;

		void initializeSceneElements();
		void setSceneElementBackground(int x, int y, Environment* background);
		void setSceneElementForeground(int x, int y, Object* foreground);

	public:
		Scene(GraphicsEngine* graphicsEngine);
		Scene(GraphicsEngine* graphicsEngine, int width, int height);
		~Scene();
		void testLevel();
		void testLevel2();
		void update();
		void display();
		void setTheme(std::string path);
		void playTheme();

		std::pair<SceneElement*, SceneElement*> getSceneElement(int x, int y);
		SceneElement* getSceneElementBackground(int x, int y);
		SceneElement* getSceneElementForeground(int x, int y);
		std::vector<SceneElement*> getNeighborForegroundElements(int e_x, int e_y);
		std::pair<int, int> getEntry();
};

