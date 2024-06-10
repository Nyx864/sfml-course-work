#include "Menu.h"
#include "Opener.h"
#include "GameSettings.h"
#include "Button.h"
#include "MovedSprite.h"
#pragma once
class SettingsMenu
{
private:
	int& menu;
	bool inSettings = true;
	Opener& opener;
	sf::Clock circle;
	sf::Font font;
	sf::Text fps;
	sf::Text winSize;
	GameSettings settings;
	GameSettings newSettings;
	MySprite backGround;
	sf::RenderWindow& window;
	Button buttonBack;
	Button buttonSave;
	Button CheckboxFullScr;
	Button CheckboxVSync;
	MovedSprite maxFPS;
	MovedSprite windowSize;
	std::vector<sf::Vector2f> variantOfSizes{
		sf::Vector2f{1120,630},
		sf::Vector2f{1280,720},
		sf::Vector2f{1440,810},
		sf::Vector2f{1600,900},
		sf::Vector2f{1760,990},
		sf::Vector2f{1920,1080} };
	std::vector<int> variantOfFPS{60,90,144,160,240,360};
		

public:
	SettingsMenu(sf::RenderWindow& window, Opener& opener, int& menu);

	~SettingsMenu();

	void open();

	void buttonsUpdate();

	void resetWindow(sf::RenderWindow& window);

	void updateMovedSprite();

	void setStartPositions();

	void event();

	void update();

	void draw();
};