#include "ball.h"
Ball ball[BallAmount];

const Vector2 BallSpeed = { 420.0f,-351.6f };
const float BallRadius = 11.0f;
const bool BallActive = false;
const bool BallStop = true;
const Color BallColor = WHITE;

void setBallParameters() {
	for (int i = 0; i < BallAmount; i++) {
		Vector2 InitialBallPos = {GetScreenWidth()/2, GetScreenHeight()-48 };
		ball[i].initPos = InitialBallPos;
		ball[i].pos = InitialBallPos;
		ball[i].speed = BallSpeed;
		ball[i].radius = BallRadius;
		ball[i].active = BallActive;
		ball[i].stop = BallStop;
		ball[i].color = BallColor;
	}
}