#pragma once
#include "SceneElement.hpp"

class Environment : public SceneElement {
	private:
		Mix_Music* m_theme;

	public:
		Environment(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path);
		~Environment();

		void display();
		void setTheme(std::string path);
		void playTheme();
};