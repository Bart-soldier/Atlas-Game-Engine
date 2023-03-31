#pragma once

#include "GraphicsEngine.hpp"
#include "Wall.hpp"
#include "Environment.hpp"

#define TILESIZE 16

class Scene {
	GraphicsEngine* m_graphicsEngine;
	int m_width;
	int m_height;

	std::vector<std::pair<Environment*, Object*>> m_sceneElements;

	public:
		Scene(GraphicsEngine* graphicsEngine, int width, int height);
		void testLevel();
		void display();
};

