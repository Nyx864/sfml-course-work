#include "Ball.h"

//!Constructors

Ball::Ball(float x, float y, bool visible, std::string imagePath) :
	visible{ visible }, sprite(imagePath,size.x,size.y)
{
	this->setPosition(x, y);
}

//!Sets

void Ball::setVisible(const bool& visible)
{
	this->visible = visible;
}

void Ball::setXSpeed(const float& xSpeed)
{
	this->xSpeed = xSpeed;
}

void Ball::setYSpeed(const float& ySpeed)
{
	this->ySpeed = ySpeed;
}

void Ball::setPosition(sf::Vector2f& point)
{
	this->sprite.getSprite().setPosition(point);
}

void Ball::setPosition(const float& x, const float& y)
{
	this->sprite.getSprite().setPosition(x, y);
}

void Ball::move(const float& x, const float& y)
{
	this->sprite.getSprite().move(x, y);
}

void Ball::falling(const float& elapsed)
{
	setYSpeed(getYSpeed() + g * elapsed * 5);
}

void Ball::bounce(sf::CircleShape circle)
{
	double angle_BallAndCircle{ acos((this->getPosition().x - circle.getPosition().x) / (2 * sqrt(pow((this->getPosition().x - circle.getPosition().x) / 2, 2) + pow((this->getPosition().y - circle.getPosition().y) / 2, 2)))) };
	float angle_BallMove( acos(this->getXSpeed() / sqrt(pow(this->getYSpeed(), 2) + pow(this->getXSpeed(), 2))) );
	double resultAngle{ 2 * angle_BallAndCircle - angle_BallMove };
	double newXSpeed{ sqrt(pow(this->getYSpeed(), 2) + pow(this->getXSpeed(), 2)) * cos(resultAngle) };
	double newYSpeed{ sqrt(pow(this->getYSpeed(), 2) + pow(this->getXSpeed(), 2)) * sin(resultAngle) };
	this->setXSpeed(newXSpeed* BOUNCE_COEFFICIENT);
	this->setYSpeed(-newYSpeed*BOUNCE_COEFFICIENT);
}

void Ball::bounce(const Direction& direction)
{
	switch (direction)
	{
	case Direction::Left: 
	case Direction::Right:
		this->setXSpeed(-getXSpeed() * BOUNCE_COEFFICIENT); 
		break;

	case Direction::Bottom: 
	case Direction::Top:
		this->setYSpeed(-getYSpeed() * BOUNCE_COEFFICIENT); 
		break;
	}
}

void Ball::setRotationSpeed(float rotationSpeed)
{
	this->rotationSpeed = rotationSpeed;
}

void Ball::rotate() 
{
	this->sprite.getSprite().setRotation(this->sprite.getSprite().getRotation()+this->getRotationSpeed());
}

//!Gets

sf::Sprite& Ball::getSprite()
{
	return sprite.getSprite();
}

sf::FloatRect Ball::getGlobalBounds()
{
	return sprite.getSprite().getGlobalBounds();
}

bool Ball::isVisible()
{
	return visible;
}

float Ball::getXSpeed()
{
	return xSpeed;
}

float Ball::getYSpeed()
{
	return ySpeed;
}

sf::Vector2f Ball::getPosition()
{
	return this->sprite.getSprite().getPosition();
}

sf::Vector2f Ball::getSize()
{
	return size;
}

bool Ball::OnGround(const int& ground)
{
	if (sprite.getSprite().getPosition().y < ground - size.y/2)
		return false;
	return true;
}

float Ball::getRotationSpeed()
{
	return this->rotationSpeed;
}
