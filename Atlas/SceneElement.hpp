#pragma once
#include "Texture.hpp"
#include "GameplayEngine.hpp"

class SceneElement {
	protected:
		int m_posX;
		int m_posY;
		int m_width;
		int m_height;
		Texture* m_texture;

		int m_directionNb;
		int m_animationNb;
		int m_frame;
		Uint32 m_timeSinceLastMov;

	public:
		SceneElement(int posX, int posY, Texture* texture = nullptr);

		virtual void display();
		//virtual bool checkCollision(int posX, int posY);
		//virtual void handleCollision(SceneElement* element);

		void setTexture(Texture* texture);

		int getPosX();
		int getPosY();
		int getWidth();
		int getHeight();
		void setPos(int x, int y);
};