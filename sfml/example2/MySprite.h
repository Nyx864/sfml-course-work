#pragma once
#include "Direction.h"
#include <string>
#include <SFML/Graphics.hpp>
const float g = 9.8f;
class MySprite
{
protected:
	const int spriteHeight;
	const int spriteWidth;
	std::string imagePath;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	Direction direction;
public:

	//!Constructors

	MySprite(std::string imagePath,	int spriteHeight, int spriteWidth);

	//!Sets

	void setPosition(sf::Vector2f& point);

	void setDirection(const Direction& direction);

	void setIcon(const std::string &imagePath);

	//!Gets

	Direction getDirection();

	int getWidth();

	int getHeight();

	sf::Sprite& getSprite();

	sf::Vector2f getPosition();
	
	std::string getImage();
};

