#pragma once
#include "raylib.h"
namespace AR {

		struct Player {
			Rectangle rec;
			Vector2 speed;
			Color color;
			bool powerUp;
		};

		extern Player player;
		extern const Vector2 PlayerSize;
		void setPlayerParameters();

}