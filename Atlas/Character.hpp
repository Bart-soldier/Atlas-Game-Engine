#pragma once
#include "SceneElement.hpp"

enum Directions {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class Character : public SceneElement {
	protected:
		int m_speedX;
		int m_speedY;
		int m_lastMov;

		int m_frame;
		Uint32 m_timeSinceLastMov;

		Mix_Chunk* m_walkingEffect;

	public:
		Character(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path, int speedX, int speedY,
			int animationNb, int directionNb = 4);
		~Character();
		void display();
		void move(int direction);
		void move(int x, int y);
		void setWalkingEffect(std::string path);
};