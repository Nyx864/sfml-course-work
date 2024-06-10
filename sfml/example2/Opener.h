#pragma once
#define OPENER_SPEED 20
#include "Direction.h"
#include "MySprite.h"
class Opener : public MySprite
{
private:
	bool opening = false;
	bool closing = false;
	Direction direction = Direction::Bottom;
public:

	Opener();

	void move(const float& elapsed);

	void setPosition(const float& x, const float& y);

	void setOpening(const Direction& dir, const bool& isMoving);

	void setOpening(const bool& isMoving);

	void setClosing(const bool& isMoving);

	void setClosing(const Direction& dir, const bool& isMoving);

	bool isOpening();

	bool isClosing();
};

