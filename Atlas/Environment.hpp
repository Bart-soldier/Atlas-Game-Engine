#pragma once
#include "SceneElement.hpp"

class Environment : public SceneElement {
	private:
		Mix_Music* m_theme;

	public:
		Environment(int posX, int posY, Texture* texture = nullptr);
		~Environment();

		void display();
		void setTheme(std::string path);
		void playTheme();
};