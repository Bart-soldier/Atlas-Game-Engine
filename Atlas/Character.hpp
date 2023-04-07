#pragma once
#include "SceneElement.hpp"
#include "Environment.hpp"
#include "Object.hpp"

class Character : public SceneElement {
	protected:
		// Speed in pixel per frame
		float m_speed;
		float m_speedX;
		float m_speedY;
		bool m_isRunning;
		int m_direction;

		Mix_Chunk* m_walkingEffect;

		void checkDirection(int direction);


	public:
		Character(int posX, int posY, Texture* texture = nullptr);
		~Character();

		void display() override;
		bool checkCollision(int posX, int posY) override;
		void handleCollision(SceneElement* element) override;
		void startMovement(int direction);
		void stopMovement(int direction);
		void toggleRun();
		virtual void move();

		void setWalkingEffect(std::string path);
};