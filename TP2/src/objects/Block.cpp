#include "Block.h"
Block block[BlockAmount];
const float BlockSpacing = 6.25f;


void setBlockParameters() {
	for (int i = 0; i < BlockAmount; i++){
		block[i].rec.width = 50.0f;
		block[i].rec.height = 15.0f;
		block[i].color = RED;
		block[i].active = false;
	}
}