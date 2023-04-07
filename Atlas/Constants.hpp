#pragma once

// Refresh rate
const int FRAME_RATE = 60;
const float TICKS_PER_FRAME = 1000 / FRAME_RATE;

// Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int TILESIZE = 16;
const int TILEFACTOR = 4;

/*enum Directions {
	NORTH,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST,
	WEST,
	NORTHWEST
};*/

enum Directions {
	NORTH,
	EAST,
	SOUTH,
	WEST
};