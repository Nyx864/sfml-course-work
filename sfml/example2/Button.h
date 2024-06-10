#pragma once
#include "GameSettings.h"
#include "MySprite.h"
class Button: public MySprite
{
private:
	bool pressed = false;
	GameSettings setting;
public:

	Button(std::string imagePath, int Height, int Width);

	void setChosen();

	void setPressed();

	void setNotChosen();

	bool mouseOnButton();

	void setNewSettings();
};

