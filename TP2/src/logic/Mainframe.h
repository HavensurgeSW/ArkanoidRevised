#pragma once
#include "raylib.h"
#include "objects/player.h"
#include "objects/ball.h"
#include "logic/LevelBuilder.h"
#include <iostream>
using namespace std;


namespace AR {
	class Mainframe {
	private:
		int _winWidth;
		int _winHeight;
		bool _pause;
		bool _mainBool;

	public:

		enum class screenID {
			menu,
			game,
			options,
		};
		screenID screenId;
		Texture2D background;

		Mainframe();
		~Mainframe();
		void init();
		void deInit();

		void setScene(int scene);
		void mainLoop();
		void menuScreen();
		void gameScreen();
		void optionsScreen();

		void update();
		void draw();
		void input();
		void collisions();


	};
}


