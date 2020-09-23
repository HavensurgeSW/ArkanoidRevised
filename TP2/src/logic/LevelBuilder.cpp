#include "LevelBuilder.h"
#include <iostream>

Vector2 coordinates = { 14.0f, 5.0f };

void setLevelOne() {
	int row = 1;
	for (int i = 0; i < BlockAmount; i++){
		if (row>BlockAmount/9){
			coordinates.y += BlockSpacing+block[i].rec.height;
			coordinates.x = 14.0f;
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