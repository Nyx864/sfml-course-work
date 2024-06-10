#pragma once
#include <fstream>
struct GameSettings
{
	bool fullScreen;
	int windowHeight;
	int windowWidth;
	bool vSync;
	int maxFPS;
};

extern void readSettings(GameSettings& settings);

extern void writeSettings(GameSettings& settings);