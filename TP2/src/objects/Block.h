#ifndef BLOCK_H
#define BLOCK_H
#include "raylib.h"
#include <iostream>

namespace AR {
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
}

#endif