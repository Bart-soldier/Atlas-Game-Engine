#include "GameplayEngine.hpp"

namespace GameplayEngine {
	bool checkCollision(float e1_x, float e1_y, float e1_w, float e1_h, float e2_x, float e2_y, float e2_w, float e2_h) {
		if ((e2_x <= e1_x && e1_x < e2_x + e2_w) || (e1_x <= e2_x && e2_x < e1_x + e1_w)) {
			if ((e2_y <= e1_y && e1_y < e2_y + e2_h) || (e1_y <= e2_y && e2_y < e1_y + e1_h)) {
				return true;
			}
		}

		return false;
	}
}