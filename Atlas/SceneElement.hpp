#pragma once
#include "Texture.hpp"

class SceneElement {
	protected:
		int m_posX;
		int m_posY;
		int m_width;
		int m_height;
		Texture* m_texture;

		int m_frame;
		Uint32 m_timeSinceLastFrame;

		bool m_isInteractable;
		bool m_toCamera;

	public:
		SceneElement(int posX, int posY, Texture* texture = nullptr);

		virtual void display();
		virtual void display(int posX, int posY, int width, int height, bool toCamera);
		//virtual bool checkCollision(int posX, int posY);
		//virtual void handleCollision(SceneElement* element);

		void setTexture(Texture* texture);

		virtual void activate();

		int getPosX();
		int getPosY();
		int getWidth();
		int getHeight();
		Texture* getTexture();
		void setPos(int x, int y);
		bool isInteractable();
};