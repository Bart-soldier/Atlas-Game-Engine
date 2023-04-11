#pragma once
#include "SceneElement.hpp"
#include "Scene.hpp"

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
		SceneElement* checkCollision(int posX, int posY, std::vector<SceneElement*> neighbors);
		void handleCollision(SceneElement* element);
		void startMovement(int direction);
		void stopMovement(int direction);
		void toggleRun();
		virtual void move(std::vector<SceneElement*> neighbors);

		void setWalkingEffect(std::string path);
};