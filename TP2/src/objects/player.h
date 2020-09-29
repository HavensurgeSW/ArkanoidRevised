#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
namespace AR {

		struct Player {
			Rectangle rec;
			Vector2 speed;
			Color color;
			bool powerUp;
			int lives;
		};

		extern Player player;
		extern const Vector2 PlayerSize;
		void setPlayerParameters();

}
#endif