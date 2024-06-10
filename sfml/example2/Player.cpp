#include "Player.h"

//!Constructors

Player::Player(std::string name, float speed, float jumpStrength, float throwStrength, std::string image):
	name{ name }, speed{ speed }, jumpStrength{ jumpStrength }, throwStrength{ throwStrength }, sprite(image, playerHeight, playerWidth)
{
}

Player::Player(Character& character) : Player(character.getName(), character.getSpeed(), character.getJumpStrength(), character.getThrowStrength(), character.getImage())
{}

Player::Player(): Player("none",0,0,0,std::string())
{
}

//!Sets

void Player::setDirection(const Direction& direction)
{
	sprite.setDirection(direction);
}

void Player::setColor(const sf::Color& color)
{
	this->getSprite().setColor(color);
}

void Player::setName(const std::string &name)
{
	this->name = name;
}

void Player::setSpeed(const float &speed)
{
	this->speed = speed;
}

void Player::setJumpStrength(const float &jumpStrength)
{
	this->jumpStrength = jumpStrength;
}

void Player::setThrowStrength(const float &throwStrength)
{
	this->throwStrength = throwStrength;
}

void Player::setYSpeed(const float& ySpeed)
{
	this->ySpeed = ySpeed;
}

void Player::setScore(const int &score)
{
	this->score = score;
}

void Player::setPosition(sf::Vector2f &point)
{
	this->sprite.getSprite().setPosition(point);
}

void Player::setPosition(const float &x, const float &y)
{
	this->sprite.getSprite().setPosition(x, y);
}

void Player::move(const float &x, const float &y)
{
	this->sprite.getSprite().move(x, y);
}

void Player::operator=(Character& character)
{
	setName(character.getName());
	setSpeed(character.getSpeed());
	setJumpStrength(character.getJumpStrength());
	setThrowStrength(character.getThrowStrength());
	sprite.setIcon(character.getImage());
}

void Player::operator=(Player player)
{
	setName(player.getName());
	setSpeed(player.getSpeed());
	setJumpStrength(player.getJumpStrength());
	setThrowStrength(player.getThrowStrength());
	sprite.setIcon(player.getImage());
}

void Player::falling(const float& elapsed)
{
	setYSpeed(getYSpeed() + g * elapsed * 5);
}

void Player::jump()
{
	setYSpeed(-jumpStrength);
}

//!Gets

Direction Player::getDirection()
{
	return sprite.getDirection();
}

std::string Player::getName()
{
	return this->name;
}

float Player::getSpeed()
{
	return this->speed;
}

float Player::getJumpStrength()
{
	return this->jumpStrength;
}

float Player::getThrowStrength()
{
	return this->throwStrength;
}

float Player::getYSpeed()
{
	return this->ySpeed;
}

int Player::getScore()
{
	return this->score;
}

std::string Player::getImage()
{
	return this->sprite.getImage();
}

int Player::getWidth()
{
	return this->sprite.getWidth();
}

int Player::getHeight()
{
	return this->sprite.getHeight();
}

sf::Sprite& Player::getSprite()
{
	return sprite.getSprite();
}

sf::FloatRect Player::getGlobalBounds()
{
	return sprite.getSprite().getGlobalBounds();
}

sf::Vector2f Player::getPosition()
{
	return sprite.getSprite().getPosition();
}

bool Player::OnGround(const int& ground)
{
	if (sprite.getSprite().getPosition().y < ground - playerHeight/2)
		return false;
	return true;
}
