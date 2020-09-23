#pragma once
#include "raylib.h"
namespace PLYR{
	struct Player {
		Rectangle rec;
		Vector2 speed;
		Color color;
		bool powerUp;
	};


	extern Player player;
	extern const Vector2 PlayerSize;
	extern const Vector2 PlayerInitPos;
	extern const Vector2 PlayerSpeed;
	void setPlayerParameters();
}