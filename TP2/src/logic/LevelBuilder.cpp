#include "LevelBuilder.h"
#include <iostream>

Vector2 coordinates = { 0.0f, 100.0f };

void setLevelOne() {
	int row = 1;
	for (int i = 0; i < BlockAmount; i++){
		if (row>8){
			coordinates.y += 6.25f;
			coordinates.x = 0;
			row = 1;
		}
		std::cout << "test"<< i << std::endl;
		block[i].rec.x = coordinates.x;
		block[i].rec.y = coordinates.y;
		coordinates.x += BlockSpacing + block[i].rec.width;
		row++;
		block[i].active = true;
	}
}