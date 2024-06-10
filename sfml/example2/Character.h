#pragma once
#include "MySprite.h"
class Character
{
private:
	std::string name;
	float speed;
	float jumpStrength;
	float throwStrength;
	std::string imagePath;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

public:

	//!Constructors

	Character(std::string name, float speed, float jumpStrength, float throwStrength, std::string image);

	//!Sets

	void setIcon(const std::string& image);

	//!Gets

	std::string getName();

	float getSpeed();

	float getJumpStrength();

	float getThrowStrength();

	std::string getImage();
};

