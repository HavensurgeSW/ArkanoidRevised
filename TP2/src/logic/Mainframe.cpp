#include "Mainframe.h"

namespace AR {
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
		background = LoadTexture("../res/background.png");
		SetExitKey(KEY_VOLUME_UP);
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

		while (!WindowShouldClose() && _mainBool) {
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
		background = LoadTexture("../res/background.png");
		Rectangle playButton;
		playButton.x = 20.0f;
		playButton.y = GetScreenHeight() / 2.0f;
		playButton.height = 30.0f;
		playButton.width = 65.0f;

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
			DrawTexture(background, 0, -250, RAYWHITE);

			DrawText(FormatText("ARKANOID"), 20, 10, 120, WHITE);

			if (CheckCollisionPointRec(GetMousePosition(), playButton))
				DrawText(FormatText("Play"), 20, GetScreenHeight() / 2, 30, RED);
			else
				DrawText(FormatText("Play"), 20, GetScreenHeight() / 2, 30, WHITE);


			if (CheckCollisionPointRec(GetMousePosition(), creditsButton))
				DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, RED);
			else
				DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, WHITE);

			if (CheckCollisionPointRec(GetMousePosition(), closeButton))
				DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, RED);
			else
				DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, WHITE);


			DrawText(FormatText("v 1.0"), GetScreenWidth() - 50, 1, 20, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), creditsButton)) {
				DrawText(FormatText("Engine: Raylib 3.0"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 3) + 20, 30, WHITE);
				DrawText(FormatText("Created by:"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 3) + 100, 30, WHITE);
				DrawText(FormatText("Matias P. Karplus"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 3) + 130, 30, WHITE);
			}
			EndDrawing();
			if (CheckCollisionPointRec(GetMousePosition(), closeButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
				exit(0);
			}
			if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
				setScene(1);
			}
		}
	}
	void Mainframe::gameScreen() {
		_pause = false;
		setBallParameters();
		setPlayerParameters();
		ball[0].active = true;
		setBlockParameters();
		setLevelThree();

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
				DrawTexture(background, 0, -250, RAYWHITE);
				DrawText("PAUSED", 10, 10, 80, WHITE);
				DrawText("RESUME [P] / [ESC]", 10, GetScreenHeight() - 80, 30, WHITE);
				DrawText("MENU [M]", 10, GetScreenHeight() - 40, 30, WHITE);
				EndDrawing();

				if (_pause) {
					if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
						_pause = false;
					}
					if (IsKeyPressed(KEY_M)) {
						screenId = screenID::menu;
					}
#if DEBUG
					std::cout << "Pause input" << std::endl;
#endif

				}

			}
		}

		UnloadTexture(background);
		for (int i = 0; i < BlockAmount; i++) {
			UnloadTexture(block[i].BlockHedron);
		}
	}
	void Mainframe::optionsScreen() {

	}
	void Mainframe::update() {

		if (ball[0].stop) {
			ball[0].pos.x = player.rec.x + player.rec.width / 2;

			ballCol[0].pos.x = ball[0].pos.x;
			ballCol[0].pos.y = ball[0].pos.y - 5.0f;
			ballCol[1].pos.x = ball[0].pos.x + 5.0f;
			ballCol[1].pos.y = ball[0].pos.y;
			ballCol[2].pos.x = ball[0].pos.x;
			ballCol[2].pos.y = ball[0].pos.y + 5.0f;
			ballCol[3].pos.x = ball[0].pos.x - 5.0f;
			ballCol[3].pos.y = ball[0].pos.y;
		}

		for (int i = 0; i < BallAmount; i++)
		{
			if (ball[i].active) {
				if (!ball[i].stop) {
					ball[i].pos.x += GetFrameTime()*ball[i].speed.x;
					ball[i].pos.y += GetFrameTime()*ball[i].speed.y;
					for (int j = 0; j < BallCollisions; j++) {
						ballCol[j].pos.x += GetFrameTime() * ball[i].speed.x;
						ballCol[j].pos.y += GetFrameTime() * ball[i].speed.y;
					}
					if (ball[i].pos.y < 0) {
						ball[i].pos.y = 12;
						ball[i].speed.y *= -1.0f;
					}
				}
			}
		}
	}
	void Mainframe::draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexture(background, 0, -250, RAYWHITE);
		DrawRectangleRec(player.rec, GOLD);
		for (int i = 0; i < BallAmount; i++) {
			if (ball[i].active) {
				DrawCircle(ball[i].pos.x, ball[i].pos.y, ball[i].radius, ball[i].color);
			}
		}
		for (int i = 0; i < BlockAmount; i++) {
			if (block[i].active) {
				DrawTexture(block[i].BlockHedron, block[i].rec.x, block[i].rec.y, RAYWHITE);
			}
		}
		if (ball[0].stop) {
			DrawText("-SPACE-", GetScreenWidth() / 2 - 70, GetScreenHeight() - 100, 30, WHITE);
		}
#if DEBUG
		for (int i = 0; i < BlockAmount; i++) {
			DrawRectangleLines(block[i].rec.x, block[i].rec.y, block[i].rec.width, block[i].rec.height, GREEN);
			DrawText(FormatText("%i", i), block[i].rec.x + (block[i].rec.width / 2), block[i].rec.y + (block[i].rec.height / 2), 2, GREEN);
		}

		DrawCircleLines(ballCol[0].pos.x, ballCol[0].pos.y, ballCol[0].radius, GREEN);
		DrawCircleLines(ballCol[1].pos.x, ballCol[1].pos.y, ballCol[1].radius, GREEN);
		DrawCircleLines(ballCol[2].pos.x, ballCol[2].pos.y, ballCol[2].radius, GREEN);
		DrawCircleLines(ballCol[3].pos.x, ballCol[3].pos.y, ballCol[3].radius, GREEN);
#endif

		EndDrawing();

	}
	void Mainframe::input() {
		if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.rec.x -= GetFrameTime()*player.speed.x;
		if ((player.rec.x) <= 0) player.rec.x = 0;
		if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.rec.x += GetFrameTime()*player.speed.x;
		if ((player.rec.x + player.rec.width) >= _winWidth) player.rec.x = _winWidth - player.rec.width;

		if (ball[0].stop)
		{
			if (IsKeyPressed(KEY_SPACE)) {
				ball[0].stop = false;
			}
		}

		if (!_pause) {
			if (IsKeyReleased(KEY_P) || IsKeyDown(KEY_ESCAPE)) {
				_pause = true;
				fflush(stdin);
			}
		}
	}
	void Mainframe::collisions() {
		//BALLS V BRICKS
		for (int i = 0; i < BlockAmount; i++) {
			if (block[i].active) {
				if (CheckCollisionCircleRec(ballCol[0].pos, ballCol[0].radius, block[i].rec)) {
					block[i].active = false;
					ball[0].speed.y *= -1.0f;
				}
				if (CheckCollisionCircleRec(ballCol[1].pos, ballCol[1].radius, block[i].rec)) {
					block[i].active = false;
					ball[0].speed.x *= -1.0f;
				}
			}
		}

		for (int i = 0; i < BallAmount; i++) {
			if (ball[i].active) {
				if (((ball[i].pos.x + ball[i].radius) >= _winWidth) || ((ball[i].pos.x - ball[i].radius) <= 0)) ball[i].speed.x *= -1;
				if ((ball[i].pos.y - ball[i].radius) <= 0) ball[i].speed.y *= -1;
				if ((ball[i].pos.y + ball[i].radius) >= _winHeight) {

				}
			}
		}

		//BALLS V PLAYER
		for (int i = 0; i < BallAmount; i++) {
			if (CheckCollisionCircleRec(ball[i].pos, ball[i].radius, player.rec)) {
				if (ball[i].speed.y > 0) {
					ball[i].speed.y *= -1;
				}
			}
		}

		//BALLS v BOTTOM
		for (int i = 0; i < BallAmount; i++) {
			if (ball[i].pos.y > GetScreenHeight()) {
				ball[i].pos = ball[i].initPos;
				ball[i].stop = true;
			}

		}
	}
}