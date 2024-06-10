#include "Pause.h"

Pause::Pause(float x, float y, float buttonWidth, float buttonHeight, float distance) :
	pauseBG("images\\pauseBG.png", 1080, 1920), buttonContinue("images\\buttonContinue.png", buttonHeight, buttonWidth),
	buttonToMenu("images\\buttonToMenu.png", buttonHeight, buttonWidth), buttonExit("images\\buttonExit.png", buttonHeight, buttonWidth),
	distance{ distance }
{
	this->pauseBG.getSprite().setOrigin(960, 540);
	this->buttonContinue.getSprite().setOrigin(buttonWidth / 2, buttonHeight / 2);
	this->buttonToMenu.getSprite().setOrigin(buttonWidth / 2, buttonHeight / 2);
	this->buttonExit.getSprite().setOrigin(buttonWidth / 2, buttonHeight / 2);
	this->setPosition(x, y);
}

void Pause::setPosition(const float& x, const float& y)
{
	this->pauseBG.getSprite().setPosition(x, y);
	this->buttonContinue.getSprite().setPosition(x, y - distance);
	this->buttonToMenu.getSprite().setPosition(x, y);
	this->buttonExit.getSprite().setPosition(x, y + distance);
}

void Pause::setOnPause(const bool& pause)
{
	this->pause = pause;
}

sf::Vector2f Pause::getPosition()
{
	return pauseBG.getPosition();
}

bool Pause::onPause()
{
	return this->pause;
}

void Pause::updateButtons()
{
    if (buttonContinue.mouseOnButton())
    {
        buttonContinue.setChosen();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            buttonContinue.setPressed();
        }
    }
    else
    {
        buttonContinue.setNotChosen();
    }

    if (buttonToMenu.mouseOnButton())
    {
        buttonToMenu.setChosen();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            buttonToMenu.setPressed();
        }
    }
    else
    {
        buttonToMenu.setNotChosen();
    }

    if (buttonExit.mouseOnButton())
    {
        buttonExit.setChosen();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            buttonExit.setPressed();
        }
    }
    else
    {
        buttonExit.setNotChosen();
    }
}