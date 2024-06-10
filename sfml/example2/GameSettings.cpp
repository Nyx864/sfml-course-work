#include "GameSettings.h"

extern void readSettings(GameSettings& settings)
{
	std::ifstream fromFile("settings.txt");
	if (fromFile)
	{
		fromFile >> settings.fullScreen;
		fromFile >> settings.windowWidth;
		fromFile >> settings.windowHeight;
		fromFile >> settings.vSync;
		fromFile >> settings.maxFPS;
	}
	else
	{
		settings.fullScreen = true;
		settings.windowWidth = 1920;
		settings.windowHeight = 1080;
		settings.vSync = false;
		settings.maxFPS = 144;

	}
	fromFile.close();
}

extern void writeSettings(GameSettings& settings)
{
	std::ofstream toFile("settings.txt");
	toFile << settings.fullScreen << std::endl;
	toFile << settings.windowWidth << std::endl;
	toFile << settings.windowHeight << std::endl;
	toFile << settings.vSync << std::endl;
	toFile << settings.maxFPS << std::endl;
	toFile.close();
}
