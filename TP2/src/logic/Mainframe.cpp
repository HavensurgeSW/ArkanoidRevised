#include "Mainframe.h"

Mainframe::Mainframe() {
	_winWidth = 800;
	_winHeight = 450;
	_pause = false;
	_mainBool = true;
	screenID screenId;
	setScene(0);
	SetTargetFPS(60);

	
}

Mainframe::~Mainframe() {
	deInit();
}
void Mainframe::init() {
	
	InitWindow(_winWidth, _winHeight, "HSS - Arkanoid (Revised)");
	SetTargetFPS(60);
	setScene(0);
}
void Mainframe::deInit() {
	CloseWindow();
}
void Mainframe::setScene(int scene) {
	switch (scene) {
	case 0:
		screenId = screenID::menu;
		break;
	case 1:
		screenId = screenID::game;
		break;
	case 2:
		screenId = screenID::options;
		break;
	}
}


void Mainframe::mainLoop() {

	while (!WindowShouldClose()&&_mainBool) {
		switch (screenId) {
		case screenID::menu:
			menuScreen();
		case screenID::game:
			gameScreen();
		case screenID::options:
			optionsScreen();
		}
	}
}

void Mainframe::menuScreen() {

	Rectangle playButton;
	playButton.x = 20.0f;
	playButton.y = GetScreenHeight() / 2.0f;
	playButton.height = 30.0f;
	playButton.width = 65.0f;
	Rectangle optionsButton;
	optionsButton.x = 20.0f;
	optionsButton.y = (GetScreenHeight() / 2) + 50.0f;
	optionsButton.height = 30.0f;
	optionsButton.width = 113.0f;

	Rectangle creditsButton;
	creditsButton.x = 20.0f;
	creditsButton.y = (GetScreenHeight() / 2) + 100.0f;
	creditsButton.height = 30.0f;
	creditsButton.width = 113.0f;
	Rectangle closeButton;
	closeButton.x = 20.0f;
	closeButton.y = (GetScreenHeight() / 2) + 150.0f;
	closeButton.height = 30.0f;
	closeButton.width = 81.25f;



	while (!WindowShouldClose() && screenId == screenID::menu&&_mainBool) {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(FormatText("ARKANOID"), 20, GetScreenHeight() / 8, 120, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), playButton))
			DrawText(FormatText("Play"), 20, GetScreenHeight() / 2, 30, RED);
		else
			DrawText(FormatText("Play"), 20, GetScreenHeight() / 2, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), optionsButton))
			DrawText(FormatText("Options"), 20, (GetScreenHeight() / 2) + 50, 30, RED);
		else
			DrawText(FormatText("Options"), 20, (GetScreenHeight() / 2) + 50, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), creditsButton))
			DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, RED);
		else
			DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), closeButton))
			DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, RED);
		else
			DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, WHITE);



		DrawText(FormatText("v 1.0"), GetScreenWidth() - 50, 1, 20, WHITE);


		if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			setScene(1);
		}

		if (CheckCollisionPointRec(GetMousePosition(), optionsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			setScene(2);
		}


		if (CheckCollisionPointRec(GetMousePosition(), creditsButton)) {
			DrawText(FormatText("Engine: Raylib 3.0"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() /3) + 20, 30, WHITE);
			DrawText(FormatText("Created by:"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 3) + 100, 30, WHITE);
			DrawText(FormatText("Matias P. Karplus"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 3) + 130, 30, WHITE);
		}


		if (CheckCollisionPointRec(GetMousePosition(), closeButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			exit(0);
		}
		EndDrawing();
	}
}
void Mainframe::gameScreen() {
	setBallParameters();
	setPlayerParameters();
	ball[0].active = true;
	setBlockParameters();
	setLevelOne();

	while (!WindowShouldClose() && screenId == screenID::game&&_mainBool) {

		if (!_pause) {
			input();
			update();
			collisions();
			draw();
		}
		else {
			BeginDrawing();
			ClearBackground(BLACK);
			DrawText("PAUSED", GetScreenWidth() / 3.0f + 20, GetScreenHeight() / 3.0f, 60, WHITE);
			DrawText("RESUME [P]", GetScreenWidth() / 3.0f + 70, GetScreenHeight() / 3.0f + 120, 30, WHITE);
			DrawText("MENU [M]", GetScreenWidth() / 3.0f + 90, GetScreenHeight() - 60.0f, 30, WHITE);
			EndDrawing();
		}

	}
}
void Mainframe::optionsScreen() {
	
}
void Mainframe::update() {

	if (ball[0].stop){
		ball[0].pos.x = player.rec.x+player.rec.width/2;
	}

	for (int i = 0; i < BallAmount; i++)
	{
		if (ball[i].active) {
			if (!ball[i].stop){
				ball[i].pos.x += GetFrameTime()*ball[i].speed.x;
				ball[i].pos.y += GetFrameTime()*ball[i].speed.y;
			}
		}
	}
}
void Mainframe::draw() {
	BeginDrawing();
	ClearBackground(BLACK);
	//FONDO?

	DrawRectangleRec(player.rec, GOLD);
	for (int i = 0; i < BallAmount; i++) {
		if (ball[i].active) {
			DrawCircle(ball[i].pos.x, ball[i].pos.y, ball[i].radius, ball[i].color);
		}
	}
	DrawRectangleRec(block[0].rec, RED);
	for (int i = 0; i < BlockAmount; i++){
		if (block[i].active){
#if DEBUG
			cout << "Drawing?" << endl;
#endif
			DrawRectangleRec(block[i].rec,RED);
		}
	}

	EndDrawing();
	
}
void Mainframe::input() {
	if (IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)) player.rec.x -= GetFrameTime()*player.speed.x;
	if ((player.rec.x) <= 0) player.rec.x = 0;
	if (IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)) player.rec.x += GetFrameTime()*player.speed.x;
	if ((player.rec.x + player.rec.width) >= _winWidth) player.rec.x = _winWidth - player.rec.width;
	
	if (ball[0].stop)
	{
		if (IsKeyPressed(KEY_SPACE)){
			ball[0].stop = false;
		}
	}

	if (_pause) {
		if (IsKeyPressed(KEY_P)) {
			_pause = false;
			fflush(stdin);
		}
		if (IsKeyPressed(KEY_M)) {
			screenId = screenID::menu;
		}
	}
	else {
		if (IsKeyPressed(KEY_P)) {
			_pause = true;
			fflush(stdin);
		}
	}
}
void Mainframe::collisions(){

	//BALLS V BRICKS
	for (int j = 0; j < BallAmount; j++){
		for (int i = 0; i < BlockAmount; i++)
		{
				if (block[i].active){
					// Hit below
					if (((ball[j].pos.y - ball[j].radius) <= (block[i].rec.y + block[i].rec.y / 2)) &&
						((ball[j].pos.y - ball[j].radius) > (block[i].rec.y + block[i].rec.y / 2 + ball[j].speed.y)) &&
						((fabs(ball[j].pos.x - block[i].rec.x)) < (block[i].rec.x / 2 + ball[j].radius * 2 / 3)) && (ball[j].speed.y < 0))
					{
						block[i].active = false;
						ball[j].speed.y *= -1;
					}
					// Hit above
					else if (((ball[j].pos.y + ball[j].radius) >= (block[i].rec.y - block[i].rec.y / 2)) &&
						((ball[j].pos.y + ball[j].radius) < (block[i].rec.y - block[i].rec.y / 2 + ball[j].speed.y)) &&
						((fabs(ball[j].pos.x - block[i].rec.x)) < (block[i].rec.x / 2 + ball[j].radius * 2 / 3)) && (ball[j].speed.y > 0))
					{
						block[i].active = false;
						ball[j].speed.y *= -1;
					}
					// Hit left
					else if (((ball[j].pos.x + ball[j].radius) >= (block[i].rec.x - block[i].rec.x / 2)) &&
						((ball[j].pos.x + ball[j].radius) < (block[i].rec.x - block[i].rec.x / 2 + ball[j].speed.x)) &&
						((fabs(ball[j].pos.y - block[i].rec.y)) < (block[i].rec.y / 2 + ball[j].radius * 2 / 3)) && (ball[j].speed.x > 0))
					{
						block[i].active = false;
						ball[j].speed.x *= -1;
					}
					// Hit right
					else if (((ball[j].pos.x - ball[j].radius) <= (block[i].rec.x + block[i].rec.x / 2)) &&
						((ball[j].pos.x - ball[j].radius) > (block[i].rec.x + block[i].rec.x / 2 + ball[j].speed.x)) &&
						((fabs(ball[j].pos.y - block[i].rec.y)) < (block[i].rec.y / 2 + ball[j].radius * 2 / 3)) && (ball[j].speed.x < 0))
					{
						block[i].active = false;
						ball[j].speed.x *= -1;
					}
				}
		
		}
	}
	//BALLS V WALLS
	for (int i = 0; i < BallAmount; i++){
		if (ball[i].active){
			if (((ball[i].pos.x + ball[i].radius) >= _winWidth) || ((ball[i].pos.x - ball[i].radius) <= 0)) ball[i].speed.x *= -1;
			if ((ball[i].pos.y - ball[i].radius) <= 0) ball[i].speed.y *= -1;
			if ((ball[i].pos.y + ball[i].radius) >= _winHeight);
		}
	}

	//BALLS V PLAYER
	for (int i = 0; i < BallAmount; i++){
		if (CheckCollisionCircleRec(ball[i].pos, ball[i].radius, player.rec)){
			if (ball[i].speed.y > 0){
				ball[i].speed.y *= -1;
			}
		}
	}
}