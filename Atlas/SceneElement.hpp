#pragma once
#include "Texture.hpp"

class SceneElement {
	protected:
		int m_posX;
		int m_posY;
		int m_width;
		int m_height;
		Texture* m_texture;

		int m_directionNb;
		int m_animationNb;

		std::vector<std::pair<SceneElement*, SceneElement*>>* m_sceneElements;
		int m_sceneElementsWidth;

	public:
		SceneElement(int posX, int posY, Texture* texture = nullptr);

		virtual void display() = 0;
		bool checkCollision(int posX, int posY);
		void handleCollision(SceneElement* element);

		void setTexture(Texture* texture);
		void setSceneElements(std::vector<std::pair<SceneElement*, SceneElement*>>* sceneElements, int width);

		int getPosX();
		int getPosY();
		int getWidth();
		int getHeight();
};