#pragma once
#include "logic/Mainframe.h"

int main(void) {
Mainframe* arkanoid = new Mainframe;
	arkanoid->init();
	arkanoid->mainLoop();

	delete arkanoid;
}