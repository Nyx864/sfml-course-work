#include "MovedSprite.h"

MovedSprite::MovedSprite(sf::Vector2f startPosition,float maxWidth, float distance, float buttonWidth, float buttonHeight, std::string imagePath):
	startPosition{ startPosition }, maxWidth{ maxWidth }, distance{ distance }, Button(imagePath, buttonHeight, buttonWidth)
{
	readSettings(settings);
	if (settings.fullScreen)
	{
		settings.windowHeight = 1080;
		settings.windowWidth = 1920;
	}
	lastPosition = startPosition.x;
}

void MovedSprite::setMoved()
{
	this->moved = true;
}

void MovedSprite::setNotMoved()
{
	this->moved = false;
}

bool MovedSprite::isMoved()
{
	return this->moved;
}

bool MovedSprite::onOtherPosition(const int& i)
{
	if (this->getPosition().x > this->startPosition.x + i * distance - CHECK_RADIUS && this->getPosition().x < this->startPosition.x + i * distance + CHECK_RADIUS)
	{
		this->setLastPosition(this->startPosition.x + i * distance);
		return true;
	}
	else return false;
}

void MovedSprite::setLastPosition(const float& lastPosition)
{
	this->lastPosition = lastPosition;
}

float MovedSprite::getLastPosition()
{
	return this->lastPosition;
}

