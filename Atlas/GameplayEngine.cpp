#include "GameplayEngine.hpp"

namespace GameplayEngine {
	bool checkCollision(int e1_x, int e1_y, int e1_w, int e1_h, int e2_x, int e2_y, int e2_w, int e2_h) {
		if ((e2_x <= e1_x && e1_x <= e2_x + e2_w) || (e1_x <= e2_x && e2_x <= e1_x + e1_w)) {
			if ((e2_y <= e1_y && e1_y <= e2_y + e2_h) || (e1_y <= e2_y&& e2_y <= e1_y + e1_h)) {
				return true;
			}
		}

		return false;
	}
}