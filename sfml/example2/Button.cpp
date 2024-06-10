#include "Button.h"

Button::Button(std::string imagePath, int Height, int Width) 
	:MySprite(imagePath, Height, Width) 
{
	readSettings(setting);
	if (setting.fullScreen)
	{
		setting.windowHeight = 1080;
		setting.windowWidth = 1920;
	}
}

void Button::setChosen()
{
	this->sprite.setTextureRect(sf::IntRect(0, spriteHeight, spriteWidth, spriteHeight));

}

void Button::setPressed()
{
	this->sprite.setTextureRect(sf::IntRect(0, spriteHeight*2, spriteWidth, spriteHeight));
}

void Button::setNotChosen()
{
	this->sprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
}

bool Button::mouseOnButton()
{
	return this->getSprite().getGlobalBounds().contains((sf::Mouse::getPosition().x - (static_cast<float>(1920) - setting.windowWidth) / 2) / (setting.windowWidth / static_cast<float>(1920)), (sf::Mouse::getPosition().y - (static_cast<float>(1080) - setting.windowHeight) / 2) / (setting.windowHeight / static_cast<float>(1080)));
}

void Button::setNewSettings()
{
	readSettings(setting);
	if (setting.fullScreen)
	{
		setting.windowHeight = 1080;
		setting.windowWidth = 1920;
	}
}

