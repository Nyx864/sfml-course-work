#include "MainMenu.h"
#define RETURN_BUTTON 13
#define BACKSPACE 8
#define SPACE 32

MainMenu::MainMenu(sf::RenderWindow& window, Opener& opener, int& menu):
	window{window}, backGround("images\\menuBG.png",1080,1920), buttonPlay("images\\MULTIPLAYER.png", 150, 300), 
	buttonExit("images\\EXIT.png", 150, 450), buttonSettings("images\\SETTINGS.png", 150, 450),
	buttonSinglePl("images\\SINGLEPLAYER.png", 150, 300), opener{ opener }, menu{ menu },
	textbox(550,50, "fonts\\Clarendon Blk BT Black.ttf"),warning("images\\warning.png",125,500)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::open()
{

	std::ifstream fromFile("CurrentPlayer.txt");
	if (fromFile) 
	{
		std::string playerName;
		fromFile >> playerName;
		textbox.setStr(playerName);
	}


	warning.getSprite().setPosition(1075, 100);

	font.loadFromFile("fonts\\BERNHC.ttf");

	topPlayer.setFont(font);
	topPlayer.setCharacterSize(40);
	topPlayer.setFillColor(sf::Color(230, 63, 24, 255));
	topPlayer.setPosition(241, 329);
	topPlayer.setString(topPlayers());

	topScore.setFont(font);
	topScore.setCharacterSize(40);
	topScore.setFillColor(sf::Color(230, 63, 24, 255));
	topScore.setPosition(700, 329);
	topScore.setString(topScores());

	textbox.setPosition(525, 100);
	backGround.getSprite().setPosition(960, 540);
	buttonPlay.getSprite().setPosition(1570, 290);
	buttonSinglePl.getSprite().setPosition(1230, 290);
	buttonSettings.getSprite().setPosition(1400, 540);
	buttonExit.getSprite().setPosition(1400,790);
	while (inMenu) 
	{
		event();
		update();
		draw();
	}
}

void MainMenu::buttonsUpdate()
{
	if (buttonPlay.mouseOnButton())
	{
		buttonPlay.setChosen();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			buttonPlay.setPressed();
		}
	}
	else
	{
		buttonPlay.setNotChosen();
	}

	if (buttonSettings.mouseOnButton())
	{
		buttonSettings.setChosen();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			buttonSettings.setPressed();
		}
	}
	else
	{
		buttonSettings.setNotChosen();
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

	if (buttonSinglePl.mouseOnButton())
	{
		buttonSinglePl.setChosen();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			buttonSinglePl.setPressed();
		}
	}
	else
	{
		buttonSinglePl.setNotChosen();
	}
}

void MainMenu::event()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::MouseButtonPressed:
			if (!opener.isClosing()) {
				if (buttonPlay.mouseOnButton())
				{
					opener.setOpening(false);
					opener.setClosing(Direction::Bottom, true);
					opener.setPosition(960, -3980);
					menu = Menu::game;
				}

				if (textbox.mouseOnButton()) {
					textbox.setLocked(false);
					textbox.setChosen();
					showWarning = false;
				}
				else
				{
					std::ofstream toFile("CurrentPlayer.txt");
					toFile << textbox.getStr();
					toFile.close();
					textbox.setLocked(true);
					textbox.setNotChosen();
				}

				if (buttonSinglePl.mouseOnButton())
				{
					if (textbox.getStr() != "") {
						opener.setOpening(false);
						opener.setClosing(Direction::Bottom, true);
						opener.setPosition(960, -3980);
						menu = Menu::singlePlayer;
					}
					else
					{
						showWarning = true;
					}
				}

				if (buttonSettings.mouseOnButton())
				{
					opener.setOpening(false);
					opener.setClosing(Direction::Left, true);
					opener.setPosition(4420, 540);
					menu = Menu::settings;
				}
				if (buttonExit.mouseOnButton())
				{
					inMenu = false;
					window.close();
				}

				
			}
			break;

		case sf::Event::TextEntered:
			if (!textbox.isLocked())
			{
				if ((event.text.unicode < 128 && event.text.unicode > 29)|| event.text.unicode == RETURN_BUTTON || event.text.unicode == BACKSPACE)
				{
					switch (event.text.unicode)
					{
					case RETURN_BUTTON:
						textbox.setLocked(true);
						textbox.setNotChosen();
						break;
					case BACKSPACE:
						textbox.removeLast();
						break;
					case SPACE:
						break;
					default:
						textbox.addSym(event.text.unicode);
						break;
					}
				}
			}
		}
	}
}

void MainMenu::update()
{
	float elapsed = circle.restart().asSeconds();
	buttonsUpdate();
	if (opener.isOpening()) {
		if (opener.getPosition().y < 3200 && opener.getPosition().y > -2500 && opener.getPosition().x > -2500 && opener.getPosition().x < 4400)
		{
			opener.move(elapsed);
		}
		else
		{
			opener.setOpening(false);
		}
	}
	else
		if (opener.isClosing())
		{
			if (opener.getPosition().y > 1080 || opener.getPosition().y < 0 || opener.getPosition().x < 0 || opener.getPosition().x > 1920)
			{
				opener.move(elapsed);
			}
			else
			{
				if (menu == Menu::game || menu == Menu::singlePlayer) {
					opener.setClosing(false);
					opener.setOpening(true);
					opener.setDirection(Direction::Top);
					inMenu = false;
				}
				if (menu == Menu::settings) {
					opener.setClosing(false);
					opener.setOpening(true);
					opener.setDirection(Direction::Left);
					inMenu = false;
				}
			}
		}
}

void MainMenu::draw()
{
	window.clear();
	window.draw(backGround.getSprite());
	if(showWarning)
		window.draw(warning.getSprite());
	textbox.draw(window);
	window.draw(topPlayer);
	window.draw(topScore);
	window.draw(buttonPlay.getSprite());
	window.draw(buttonSettings.getSprite());
	window.draw(buttonSinglePl.getSprite());
	window.draw(buttonExit.getSprite());
	window.draw(opener.getSprite());
	window.display();
}

std::string MainMenu::topPlayers()
{
	std::string topPlayers;
	std::ifstream fromFile("scores.txt");
	std::string str;
	for (int i = 0; i < 10; ++i) {
		if (fromFile && !fromFile.eof())
		{
			fromFile >> str;
			topPlayers += str+'\n';
			fromFile >> str;
		}
		else 
		{
			topPlayers += "No_Data\n";
		}
	}
	fromFile.close();
	return topPlayers;
}

std::string MainMenu::topScores()
{
	std::string topScores;
	std::ifstream fromFile("scores.txt");
	std::string str;
	for (int i = 0; i < 10; ++i) {
		if (fromFile && !fromFile.eof())
		{
			fromFile >> str;
			fromFile >> str;
			topScores += str + '\n';
		}
		else
		{
			topScores += "0\n";
		}
	}
	fromFile.close();
	return topScores;
}