#pragma once
#include "Character.h"	
const int playerHeight = 130;
const int playerWidth = 60;
class Player
{
private:
	std::string name;
	float speed;
	float jumpStrength;
	float throwStrength;
	MySprite sprite;
	float ySpeed = 0;
	int score = 0;
public:

	//!Constructors

	Player(std::string name, float speed, float jumpStrength, float throwStrength, std::string image);
	
	Player(Character& character);

	Player();

	//!Sets

	void setDirection(const Direction& direction);

	void setColor(const sf::Color& color);

	void setName(const std::string &name);

	void setSpeed(const float &speed);

	void setJumpStrength(const float& jumpStrength);

	void setThrowStrength(const float &throwStrength);

	void setYSpeed(const float& ySpeed);

	void setScore(const int &score);

	void setPosition(sf::Vector2f &point);

	void setPosition(const float& x, const float& y);

	void move(const float &x, const float &y);

	void operator= (Character& character);

	void operator=(Player player);

	void falling(const float& elapsed);

	void jump();

	//!Gets

	Direction getDirection();

	std::string getName();

	float getSpeed();

	float getJumpStrength();

	float getThrowStrength();

	float getYSpeed();

	int getScore();

	std::string getImage();

	int getWidth();

	int getHeight();

	sf::Sprite& getSprite();

	sf::FloatRect getGlobalBounds();

	sf::Vector2f getPosition();

	bool OnGround(const int& ground);
};

