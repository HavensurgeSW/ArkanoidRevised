#include "player.h"

namespace AR {
	
		Player player;
		const Vector2 PlayerSize = { 95.0f, 12.0f };
		const Vector2 PlayerSpeed = { 500.0f,120.0f };

		void setPlayerParameters() {
			player.rec.width = PlayerSize.x;
			player.rec.height = PlayerSize.y;
			Vector2 PlayerInitPos = { (GetScreenWidth() / 2) - (player.rec.width / 2),  420.0f };
			player.rec.x = PlayerInitPos.x;
			player.rec.y = PlayerInitPos.y;
			player.speed.x = PlayerSpeed.x;
			player.speed.y = PlayerSpeed.y;
			player.color = GOLD;
			bool powerUp = false;
		}

	
}


