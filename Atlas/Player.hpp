#pragma once
#include "Character.hpp"

class Player : public Character {
	private:
		Camera* m_camera;

	public:
		Player(int posX, int posY, Texture* texture = nullptr);
		void move() override;
		void setCamera(Camera* camera);
};

