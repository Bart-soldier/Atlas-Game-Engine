#include "Wall.hpp"

Wall::Wall(GraphicsEngine* graphicsEngine, int posX, int posY, std::string path) : Object(graphicsEngine, posX, posY, path) {
}

Wall::Wall(int posX, int posY) : Object(posX, posY) {
}