#pragma once
#include "Character.hpp"

class Player : public Character {
	private:
		Camera* m_camera;

	public:
		Player(int posX, int posY, int speedX, int speedY, Texture* texture = nullptr);
		void move(int direction) override;
		void move(int x, int y) override;
		void setCamera(Camera* camera);
};

