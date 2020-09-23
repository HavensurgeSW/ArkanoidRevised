#include "LevelBuilder.h"

Vector2 coordinates = { 0.0f, 100.0f };

void setLevelOne() {
	int row = 1;
	for (int i = 0; i < BlockAmount; i++){
		if (row>8){
			coordinates.y += 6.25f;
			coordinates.x = 0;
		}
		block[i].rec.x = coordinates.x;
		coordinates.x += BlockSpacing + block[i].rec.x;
		row++;
		block[i].active = true;
	}
}