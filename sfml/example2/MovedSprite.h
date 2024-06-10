#pragma once
#include "Button.h"
#define CHECK_RADIUS 35

class MovedSprite: public Button
{
protected:
	bool moved=false;
	float maxWidth;
	float distance;
	GameSettings settings;
	sf::Vector2f startPosition;
	float lastPosition;
public:
	MovedSprite(sf::Vector2f startPosition, float maxWidth, float distance, float buttonWidth, float buttonHeight, std::string imagePath);

	void setMoved();

	void setNotMoved();

	bool isMoved();

	bool onOtherPosition(const int& i);
		
	void setLastPosition(const float& lastPosition);

	float getLastPosition();
};

