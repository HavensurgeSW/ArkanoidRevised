#pragma once
#include "raylib.h"
#include <iostream>
struct Block {
	Rectangle rec;
	Color color;
	bool active;
	Texture2D BlockHedron;
};

const int BlockAmount = 72;
extern Block block[BlockAmount];
extern const float BlockSpacing;

void setBlockParameters();