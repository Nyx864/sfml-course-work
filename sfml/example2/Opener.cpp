#include "Opener.h"

Opener::Opener()
	:MySprite("images\\opener.png",5000,5000)
{
}

void Opener::move(const float &elapsed)
{
	switch (direction) 
	{
	case Direction::Bottom:
		this->getSprite().setPosition(this->getSprite().getPosition().x, this->getSprite().getPosition().y + OPENER_SPEED * elapsed * 144);
		break;
	case Direction::Top:
		this->getSprite().setPosition(this->getSprite().getPosition().x, this->getSprite().getPosition().y - OPENER_SPEED * elapsed * 144);
		break;
	case Direction::Left:
		this->getSprite().setPosition(this->getSprite().getPosition().x - OPENER_SPEED * elapsed * 144, this->getSprite().getPosition().y);
		break;
	case Direction::Right:
		this->getSprite().setPosition(this->getSprite().getPosition().x + OPENER_SPEED * elapsed * 144, this->getSprite().getPosition().y);
		break;
	}
}

void Opener::setPosition(const float& x, const float& y)
{
	this->getSprite().setPosition(x,y);
}

void Opener::setOpening(const Direction& dir, const bool& isMoving)
{
	this->direction = dir;
	this->opening = isMoving;
}

void Opener::setOpening(const bool& isMoving)
{
	this->opening = isMoving;
}

void Opener::setClosing(const bool& isMoving)
{
	this->closing = isMoving;
}

void Opener::setClosing(const Direction& dir, const bool& isMoving)
{
	this->direction = dir;
	this->closing = isMoving;
}

bool Opener::isOpening()
{
	return this->opening;
}

bool Opener::isClosing()
{
	return this->closing;
}
