#pragma once
#include "SceneElement.hpp"
#include "Scene.hpp"
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

		Scene* m_scene;

		Mix_Chunk* m_walkingEffect;

		void checkDirection(int direction);


	public:
		Character(int posX, int posY, Texture* texture = nullptr);
		~Character();

		void display() override;
		SceneElement* checkCollision(int posX, int posY);
		void handleCollision(SceneElement* element);
		void startMovement(int direction);
		void stopMovement(int direction);
		void toggleRun();
		virtual void move();
		void addToScene(Scene* scene);

		void setWalkingEffect(std::string path);
};