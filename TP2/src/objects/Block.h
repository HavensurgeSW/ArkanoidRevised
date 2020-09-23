#pragma once
#include "raylib.h"
struct Block {
	Rectangle rec;
	Color color;
	bool active;
};

const int BlockAmount = 72;
extern Block block[BlockAmount];
extern const float BlockSpacing;

void setBlockParameters();