#include "LevelBuilder.h"
#include <iostream>

namespace AR {

	Vector2 coordinates = { 14.0f, 5.0f };
	void createBlocks() {
		int row = 1;
		for (int i = 0; i < BlockAmount; i++) {
			if (row > BlockAmount / 9) {
				coordinates.y += BlockSpacing + block[i].rec.height;
				coordinates.x = 14.0f;
				row = 1;
			}
#if DEBUG
			std::cout << "Created Block " << i << std::endl;
#endif
			block[i].rec.x = coordinates.x;
			block[i].rec.y = coordinates.y;
			coordinates.x += BlockSpacing + block[i].rec.width;
			row++;
			block[i].active = true;
		}
		coordinates = { 14.0f, 5.0f };

	}

	void setLevelOne() {
		createBlocks();
		block[3].active = false;
		block[4].active = false;
		block[11].active = false;
		block[12].active = false;
		block[19].active = false;
		block[20].active = false;
		block[24].active = false;
		block[25].active = false;
		block[26].active = false;
		block[27].active = false;
		block[28].active = false;
		block[29].active = false;
		block[30].active = false;
		block[31].active = false;
		block[32].active = false;
		block[33].active = false;
		block[34].active = false;
		block[35].active = false;
		block[36].active = false;
		block[37].active = false;
		block[38].active = false;
		block[39].active = false;
		block[40].active = false;
		block[41].active = false;
		block[42].active = false;
		block[43].active = false;
		block[44].active = false;
		block[45].active = false;
		block[46].active = false;
		block[47].active = false;
		block[51].active = false;
		block[52].active = false;
		block[59].active = false;
		block[60].active = false;
		block[67].active = false;
		block[68].active = false;
	}

	void setLevelTwo() {
		createBlocks();
		for (int i = 0; i < BlockAmount; i++) {
			block[i].active = false;
		}

		block[19].active = true;
		block[20].active = true;
		block[26].active = true;
		block[27].active = true;
		block[28].active = true;
		block[29].active = true;
		block[33].active = true;
		block[34].active = true;
		block[35].active = true;
		block[36].active = true;
		block[37].active = true;
		block[38].active = true;
		block[42].active = true;
		block[43].active = true;
		block[44].active = true;
		block[45].active = true;
		block[51].active = true;
		block[52].active = true;

	}

	void setLevelThree() {
		setLevelTwo();

		for (int i = 0; i < BlockAmount; i++) {
			if (block[i].active) {
				block[i].active = false;
			}
			else {
				block[i].active = true;
			}
		}

		block[3].active = false;
		block[4].active = false;
		block[11].active = false;
		block[12].active = false;
		block[59].active = false;
		block[60].active = false;
		block[67].active = false;
		block[68].active = false;
	}
}