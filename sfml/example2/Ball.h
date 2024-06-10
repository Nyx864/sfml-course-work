#pragma once
#include "MySprite.h"
#include "Direction.h"
#define BOUNCE_COEFFICIENT 0.75
#define PI 3.14159
	const sf::Vector2f size{ 50,50 };
class Ball
{
private:
	float rotationSpeed;
	bool visible;
	float ySpeed;
	float xSpeed;
	MySprite sprite;
public:

	//!Constructors

	Ball(float x, float y, bool visible, std::string imagePath);

	//!Sets

	void setVisible(const bool& visible);

	void setXSpeed(const float& xSpeed);

	void setYSpeed(const float& ySpeed);

	void setPosition(sf::Vector2f& point);

	void setPosition(const float& x, const float& y);

	void move(const float& x, const float& y);

	void falling(const float &elapsed);

	void bounce(sf::CircleShape circle);

	void bounce(const Direction &direction);

	void setRotationSpeed(float rotationSpeed);

	void rotate();

	//!Gets

	sf::Sprite& getSprite();

	sf::FloatRect getGlobalBounds();

	bool isVisible();

	float getXSpeed();

	float getYSpeed();

	sf::Vector2f getPosition();

	sf::Vector2f getSize();

	bool OnGround(const int& ground);

	float getRotationSpeed();
};

