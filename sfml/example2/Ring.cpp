#include "Ring.h"

Ring::Ring(float radius, float ringThickness, float lineThickness) :
	ringThickness{ ringThickness }, radius{ radius }, sprite("images\\ring.png", 91, 112)
{
	line.setSize(sf::Vector2f(radius * 2, lineThickness));
	leftCircle.setRadius(ringThickness);
	rightCircle.setRadius(ringThickness);
	constructRing(radius, ringThickness, lineThickness);
}

void Ring::constructRing(const float& radius, const float& ringThickness, const float& lineThickness)
{
	sprite.getSprite().setOrigin(56, 2);
	line.setOrigin(radius, lineThickness / 2);
	leftCircle.setOrigin(ringThickness, ringThickness);
	rightCircle.setOrigin(ringThickness, ringThickness);
	line.setPosition(ringThickness, ringThickness);
	rightCircle.setPosition(radius * 2 + ringThickness, 0);
}

void Ring::setPosition(sf::Vector2f point)
{
	sprite.getSprite().setPosition(point);
	leftCircle.setPosition(point.x-this->radius,point.y);
	rightCircle.setPosition(point.x+this->radius,point.y);
	line.setPosition(point);
}

sf::Vector2f Ring::getRightCirclePosition()
{
	return rightCircle.getPosition();
}

sf::Vector2f Ring::getLeftCirclePosition()
{
	return leftCircle.getPosition();
}

sf::FloatRect Ring::getLineGlobalBounds()
{
	return line.getGlobalBounds();
}

sf::FloatRect Ring::getRightGlobalBounds()
{
	return rightCircle.getGlobalBounds();
}

sf::FloatRect Ring::getLeftGlobalBounds()
{
	return leftCircle.getGlobalBounds();
}

sf::CircleShape Ring::getLeftSprite()
{
	return leftCircle;
}

sf::RectangleShape Ring::getLineSprite()
{
	return line;
}

sf::CircleShape Ring::getRightSprite()
{
	return rightCircle;
}

float Ring::getRingThickness()
{
	return ringThickness;
}

sf::Vector2f Ring::getPosition()
{
	return line.getPosition();
}

float Ring::getRadius() {
	return this->radius;
}

sf::Sprite& Ring::getSprite()
{
	return this->sprite.getSprite();
}

