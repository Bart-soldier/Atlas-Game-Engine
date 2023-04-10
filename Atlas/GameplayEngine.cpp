#include "GameplayEngine.hpp"
#include <stdio.h>

namespace GameplayEngine {
	bool checkCollision(SDL_Rect e1_hb, SDL_Rect e2_hb) {
		printf("e1: x = %d, y = %d, w = %d, h = %d\n", e1_hb.x, e1_hb.y, e1_hb.w, e1_hb.h);
		printf("e2: x = %d, y = %d, w = %d, h = %d\n", e2_hb.x, e2_hb.y, e2_hb.w, e2_hb.h);

		if ((e2_hb.x <= e1_hb.x && e1_hb.x < e2_hb.x + e2_hb.w) || (e1_hb.x <= e2_hb.x && e2_hb.x < e1_hb.x + e1_hb.w)) {
			if ((e2_hb.y <= e1_hb.y && e1_hb.y < e2_hb.y + e2_hb.h) || (e1_hb.y <= e2_hb.y && e2_hb.y < e1_hb.y + e1_hb.h)) {
				return true;
			}
		}

		return false;
	}
}