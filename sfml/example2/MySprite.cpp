#include "MySprite.h"

//!Constructors

MySprite::MySprite(std::string imagePath, int spriteHeight, int spriteWidth):
	imagePath{ imagePath }, spriteHeight{ spriteHeight }, spriteWidth{ spriteWidth }
{
	this->image.loadFromFile(imagePath);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->getWidth(), this->getHeight()));
	this->sprite.setOrigin(this->getWidth() / 2, this->getHeight() / 2);
}

//!Sets

void MySprite::setPosition(sf::Vector2f& point)
{
	this->sprite.setPosition(point);
}

void MySprite::setDirection(const Direction& direction)
{
	this->direction = direction;
}

void MySprite::setIcon(const std::string &imagePath)
{
	this->image.loadFromFile(imagePath);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->getWidth(), this->getHeight()));
}

//!Gets

Direction MySprite::getDirection()
{
	return this->direction;
}

int MySprite::getWidth()
{
	return spriteWidth;
}

int MySprite::getHeight() {
	return spriteHeight;
}

sf::Sprite& MySprite::getSprite()
{
	return sprite;
}

sf::Vector2f MySprite::getPosition()
{
	return this->sprite.getPosition();
}


std::string MySprite::getImage()
{
	return this->imagePath;
}
