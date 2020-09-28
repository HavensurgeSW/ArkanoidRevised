#pragma once
#include "logic/Mainframe.h"
using namespace AR;

int main(void) {
Mainframe* arkanoid = new Mainframe;
	arkanoid->init();
	arkanoid->mainLoop();

	delete arkanoid;
}