#pragma once
#include <typeinfo>

#include "GraphicsEngine.hpp"
#include "Player.hpp"
#include "Text.hpp"
#include "Timer.hpp"
#include "Scene.hpp"

class GameplayEngine {
	private:
		// Window elements
		GraphicsEngine* m_graphicsEngine;
		int m_exitStatus;

		// Game Elements
		Player* m_player;
		std::vector<Scene*> m_scenes;
		int m_currentScene;

		// FPS counting and caping
		Text* m_fpsCounter;
		Timer m_fpsTimer;
		Timer m_fpsCapTimer;
		int m_countedFrames;

		void handleEvent();
		void movePlayer();

		void enterScene();
		void leaveScene();

		Object* checkInteractable(int x, int y);
		void interact(std::pair<int, int> interaction);

		void gameLoop();
		void update();
		void display();

	public:
		GameplayEngine(GraphicsEngine* graphicsEngine);

		void startGame();
};

