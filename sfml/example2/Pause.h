#pragma once
#include "Button.h"
class Pause
{
public:
	MySprite pauseBG;
	Button buttonContinue;
	Button buttonToMenu;
	Button buttonExit;
	bool pause = false;
	float distance;
	Pause(float x, float y, float width, float height, float distance);

	void setPosition(const float& x, const float& y);

	void setOnPause(const bool& pause);

	sf::Vector2f getPosition();

	bool onPause();

	void updateButtons();
};