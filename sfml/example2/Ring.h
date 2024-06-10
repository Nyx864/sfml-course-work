#pragma once
#include <SFML/Graphics.hpp>
#include "MySprite.h"
class Ring
{
private:
	sf::CircleShape leftCircle;
	sf::CircleShape rightCircle;
	sf::RectangleShape line;
	MySprite sprite;
	float radius;
	float ringThickness;
public:
	Ring(float radius, float ringThickness, float lineThickness);

	void constructRing(const float& radius, const float& ringThickness, const float& lineThickness);

	void setPosition(sf::Vector2f point);

	sf::Vector2f getRightCirclePosition();

	sf::Vector2f getLeftCirclePosition();

	sf::FloatRect getLineGlobalBounds();

	sf::FloatRect getRightGlobalBounds();

	sf::FloatRect getLeftGlobalBounds();

	sf::CircleShape getLeftSprite();

	sf::RectangleShape getLineSprite();

	sf::CircleShape getRightSprite();

	float getRingThickness();

	sf::Vector2f getPosition();

	float getRadius();

	sf::Sprite& getSprite();
};

