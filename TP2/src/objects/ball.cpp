#include "ball.h"

namespace AR {

	Ball ball[BallAmount];
	Ball ballCol[BallCollisions];

	const Vector2 BallSpeed = { 350.0f,-251.6f };
	const float BallRadius = 9.0f;
	const bool BallActive = false;
	const bool BallStop = true;
	const Color BallColor = WHITE;

	void setBallParameters() {
		Vector2 InitialBallPos = { GetScreenWidth() / 2, GetScreenHeight() - 48 };
		for (int i = 0; i < BallAmount; i++) {

			ball[i].initPos = InitialBallPos;
			ball[i].pos = InitialBallPos;
			ball[i].speed = BallSpeed;
			ball[i].radius = BallRadius;
			ball[i].active = BallActive;
			ball[i].stop = BallStop;
			ball[i].color = BallColor;
		}
		ballCol[0].initPos.y = InitialBallPos.y - 5.0f;
		ballCol[0].initPos.x = InitialBallPos.x;

		ballCol[1].initPos.x = InitialBallPos.x + 5.0f;
		ballCol[1].initPos.y = InitialBallPos.y;

		ballCol[2].initPos.y = InitialBallPos.y + 5.0f;
		ballCol[2].initPos.x = InitialBallPos.x;

		ballCol[3].initPos.x = InitialBallPos.x - 5.0f;
		ballCol[3].initPos.y = InitialBallPos.y;
		for (int i = 0; i < BallCollisions; i++) {
			ballCol[i].pos = ballCol[i].initPos;
			ballCol[i].speed = BallSpeed;
			ballCol[i].radius = BallRadius;
			ballCol[i].active = BallActive;
			ballCol[i].stop = BallStop;
			ballCol[i].color = BallColor;
		}

	}
}