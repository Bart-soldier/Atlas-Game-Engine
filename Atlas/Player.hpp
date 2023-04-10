#pragma once
#include "Character.hpp"

class Player : public Character {
	private:
		Camera* m_camera;

	public:
		Player(int posX, int posY, Texture* texture = nullptr);
		void move() override;
		bool checkInteractable(int x, int y);

		void setCamera(Camera* camera);
};

