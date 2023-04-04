/*#include "GameplayEngine.hpp"

namespace GameplayEngine {
	bool checkCollision(SceneElement* element1, SceneElement* element2) {
		int e1_x = element1->getPosX();
		int e1_y = element1->getPosY();
		int e1_w = element1->getWidth();
		int e1_h = element1->getHeight();

		int e2_x = element2->getPosX();
		int e2_y = element2->getPosY();
		int e2_w = element2->getWidth();
		int e2_h = element2->getHeight();

		if ((e2_x < e1_x && e2_x + e2_w > e1_x) || (e2_x > e1_x && e2_x < e1_x + e1_w)) {
			if ((e2_y < e1_y && e2_y + e2_h > e1_y) || (e2_y > e1_y && e2_y < e1_y + e1_h)) {
				return true;
			}
		}

		return false;
	}

	std::vector<SceneElement*> neighborElements(SceneElement* element, std::vector<SceneElement*> sceneElements) {
		std::vector<SceneElement*> neighborElements;

		return neighborElements;
	}
}*/