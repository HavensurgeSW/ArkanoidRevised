#pragma once
#include "raylib.h"
#include "objects/player.h"
#include "objects/ball.h"
#include <iostream>
using namespace std;
using namespace PLYR;


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


