#include "Character.h"

Character::Character(std::string name, float speed, float jumpStrength, float throwStrength, std::string image):
	name{ name }, speed{ speed }, jumpStrength{ jumpStrength }, throwStrength{ throwStrength }, imagePath{image}
{
	this->setIcon(image);
}

void Character::setIcon(const std::string& image)
{
	this->image.loadFromFile(image);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
}

std::string Character::getName()
{
	return this->name;
}

float Character::getSpeed()
{
	return this->speed;
}

float Character::getJumpStrength()
{
	return this->jumpStrength;
}

float Character::getThrowStrength()
{
	return this->throwStrength;
}

std::string Character::getImage()
{
	return this->imagePath;
}