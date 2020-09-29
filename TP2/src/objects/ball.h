#ifndef BALL_H
#define BALL_H
#include "raylib.h"
namespace AR {
	struct Ball {
		Vector2 initPos;
		Vector2 pos;
		Vector2 speed;
		float radius;
		bool active;
		bool stop;
		Color color;
	};
	const int BallAmount = 5;
	const int BallCollisions = 4;

	extern Ball ball[BallAmount];
	extern Ball ballCol[BallCollisions];

	extern const Vector2 InitialBallPos;
	extern const Vector2 BallSpeed;
	extern const float BallRadius;
	extern const bool BallActive;
	extern const bool BallStop;
	extern const Color BallColor;

	void setBallParameters();
}
#endif

