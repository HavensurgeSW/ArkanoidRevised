#include "Block.h"

namespace AR {
	Block block[BlockAmount];
	const float BlockSpacing = 6.25f;


	void setBlockParameters() {
		for (int i = 0; i < BlockAmount; i++) {
			block[i].rec.width = 90.0f;
			block[i].rec.height = 25.0f;
			block[i].color = RED;
			block[i].active = false;
			block[i].BlockHedron = LoadTexture("../res/HedronBlock.png");
#if DEBUG
			std::cout << "Texture load" << std::endl;
#endif
		}
	}
}