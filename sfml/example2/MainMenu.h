#pragma once
#include "Opener.h"
#include "Menu.h"
#include "Button.h"
#include "TextBox.h"
class MainMenu
{
private:
	int& menu;
	bool inMenu = true;
	sf::Clock circle;
	MySprite backGround;
	sf::RenderWindow& window;
	Button buttonPlay;
	Button buttonSinglePl;
	Button buttonSettings;
	Button buttonExit;
	Opener& opener;
	TextBox textbox;

	sf::Text topPlayer;
	sf::Text topScore;
	sf::Font font;
	MySprite warning;
	bool showWarning = false;

public:
	MainMenu(sf::RenderWindow& window, Opener& opener, int& menu);

	~MainMenu();

	void open();

	void buttonsUpdate();

	void event();

	void update();

	void draw();

	std::string topPlayers();

	std::string topScores();
};

