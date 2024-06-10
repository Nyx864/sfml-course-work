#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(sf::RenderWindow& window, Opener& opener, int& menu) :
	window{ window }, backGround("images\\settingsBG.png", 1080, 1920), buttonBack("images\\BACK.png", 75, 225),
	CheckboxFullScr("images\\Checkbox.png", 50, 50), CheckboxVSync("images\\Checkbox.png", 50, 50),
	buttonSave("images\\SAVE.png", 75, 225), maxFPS(sf::Vector2f(800,440),800,160,55,55,"images\\MovedSprite.png"),
	windowSize(sf::Vector2f(800, 640), 800, 160, 55, 55, "images\\MovedSprite.png"),
	opener{ opener }, menu{ menu }
{
	readSettings(settings);
	newSettings = settings;
}

SettingsMenu::~SettingsMenu()
{
}

void SettingsMenu::open()
{
	
	setStartPositions();
	opener.setOpening(true);
	opener.setDirection(Direction::Top);
	while (inSettings)
	{
		event();
		update();
		draw();
	}
}

void SettingsMenu::buttonsUpdate()
{
    if (buttonBack.mouseOnButton())
    {
        buttonBack.setChosen();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            buttonBack.setPressed();
        }
    }
    else
    {
        buttonBack.setNotChosen();
    }

	if (buttonSave.mouseOnButton())
	{
		buttonSave.setChosen();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			buttonSave.setPressed();
		}
	}
	else
	{
		buttonSave.setNotChosen();
	}

	if (CheckboxFullScr.mouseOnButton())
	{
		CheckboxFullScr.setChosen();
	}
	else
	{
		CheckboxFullScr.setNotChosen();
	}

	if (CheckboxVSync.mouseOnButton())
	{
		CheckboxVSync.setChosen();
	}
	else
	{
		CheckboxVSync.setNotChosen();
	}

	if (newSettings.fullScreen)
	{
		CheckboxFullScr.setPressed();
	}

	if (newSettings.vSync)
	{
		CheckboxVSync.setPressed();
	}
}

void SettingsMenu::resetWindow(sf::RenderWindow& window)
{
	GameSettings set;
	readSettings(set);
	
	if(set.fullScreen) window.create(sf::VideoMode(1920, 1080), "game", sf::Style::None);
	else window.create(sf::VideoMode(set.windowWidth, set.windowHeight), "game", sf::Style::None);

	if (set.vSync) window.setVerticalSyncEnabled(true);
	else window.setFramerateLimit(set.maxFPS);

	sf::View view(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080));
	window.setView(view);
	if(settings.fullScreen) window.setPosition(sf::Vector2i(view.getCenter().x - 1920 / 2, view.getCenter().y - 1080 / 2));
	else window.setPosition(sf::Vector2i(view.getCenter().x - set.windowWidth / 2, view.getCenter().y - set.windowHeight / 2));
}

void SettingsMenu::updateMovedSprite()
{
	if (windowSize.isMoved()) {
		
		sf::Vector2f newPosition; 
		if(settings.fullScreen) newPosition = sf::Vector2f(sf::Mouse::getPosition().x, windowSize.getPosition().y);
		else newPosition = sf::Vector2f((sf::Mouse::getPosition().x - (static_cast<float>(1920) - settings.windowWidth) / 2) / (settings.windowWidth / static_cast<float>(1920)), windowSize.getPosition().y);
		if (newPosition.x > 800 && newPosition.x < 1600) {
			windowSize.setPosition(newPosition);
			for (int i = 0; i < 6; ++i)
			{
				if (windowSize.onOtherPosition(i))
				{
					newSettings.windowWidth = variantOfSizes[i].x;
					newSettings.windowHeight = variantOfSizes[i].y;
				}
			}
		}
	}
	else 
	{
		windowSize.getSprite().setPosition(windowSize.getLastPosition(), windowSize.getPosition().y);
		windowSize.setNotChosen();
	}

	if (maxFPS.isMoved()) {
		maxFPS.setChosen();
		sf::Vector2f newPosition;
		newPosition = sf::Vector2f((sf::Mouse::getPosition().x - (static_cast<float>(1920) - settings.windowWidth) / 2) / (settings.windowWidth / static_cast<float>(1920)), maxFPS.getPosition().y);
		if (newPosition.x > 800 && newPosition.x < 1600) {
			maxFPS.setPosition(newPosition);
			for (int i = 0; i < 6; ++i)
			{
				if (maxFPS.onOtherPosition(i))
				{
					newSettings.maxFPS = variantOfFPS[i];
				}
			}
		}
	}
	else
	{
		maxFPS.getSprite().setPosition(maxFPS.getLastPosition(), maxFPS.getPosition().y);
	}
}

void SettingsMenu::setStartPositions()
{
	font.loadFromFile("fonts\\Clarendon Blk BT Black.ttf");
	fps.setFont(font);
	fps.setCharacterSize(50);
	fps.setPosition(1050, 270);
	fps.setFillColor(sf::Color::White);
	winSize.setFont(font);
	winSize.setCharacterSize(50);
	winSize.setPosition(850, 760);
	winSize.setFillColor(sf::Color::White);
	windowSize.getSprite().setPosition(0, 640);
	maxFPS.getSprite().setPosition(0, 440);
	for (int i = 0; i < 6; ++i)
	{
		if (settings.windowWidth == variantOfSizes[i].x)
		{
			windowSize.setLastPosition(800 + 160 * i);
		}
		if (settings.maxFPS == variantOfFPS[i])
		{
			maxFPS.setLastPosition(800 + 160 * i);
		}
	}
	backGround.getSprite().setPosition(960, 540);
	buttonBack.getSprite().setPosition(200, 100);
	buttonSave.getSprite().setPosition(1700, 950);
	CheckboxFullScr.getSprite().setPosition(600, 640);
	CheckboxVSync.getSprite().setPosition(600, 440);
}

void SettingsMenu::event()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::MouseButtonPressed:
			if (buttonBack.mouseOnButton())
			{
				menu = Menu::mainMenu;
				opener.setClosing(Direction::Right, true);
				opener.setOpening(false);
			}

			if (buttonSave.mouseOnButton())
			{
				writeSettings(newSettings);
				readSettings(settings);
				resetWindow(window);
				windowSize.setNewSettings();
				maxFPS.setNewSettings();
				buttonBack.setNewSettings();
				buttonSave.setNewSettings();
				CheckboxFullScr.setNewSettings();
				CheckboxVSync.setNewSettings();
			}

			if (CheckboxFullScr.mouseOnButton())
			{
				if (newSettings.fullScreen) newSettings.fullScreen = false;
				else newSettings.fullScreen = true;
			}

			if (CheckboxVSync.mouseOnButton())
			{
				if (newSettings.vSync) newSettings.vSync = false;
				else newSettings.vSync = true;
			}

			if (maxFPS.mouseOnButton())
			{
				maxFPS.setMoved(); 
				maxFPS.setChosen();
			}

			if (windowSize.mouseOnButton())
			{
				windowSize.setMoved();
				windowSize.setChosen();
			}
			break;
		case sf::Event::MouseButtonReleased:

			if (maxFPS.isMoved())
			{
				maxFPS.setNotChosen();
				maxFPS.setNotMoved();
			}

			if (windowSize.isMoved())
			{
				windowSize.setNotChosen();
				windowSize.setNotMoved();
			}
		}
	}
}

void SettingsMenu::update()
{
	float elapsed = circle.restart().asSeconds();
	fps.setString("fps: " + std::to_string(newSettings.maxFPS));
	winSize.setString("Window size: " + std::to_string(newSettings.windowWidth) + "x" + std::to_string(newSettings.windowHeight));
	buttonsUpdate();
	updateMovedSprite();
	if (opener.isOpening()) {
		if (opener.getPosition().y < 4580 && opener.getPosition().y > -5000 && opener.getPosition().x > -2500 && opener.getPosition().x < 3500)
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
				opener.setClosing(false);
				opener.setOpening(true);
				opener.setDirection(Direction::Left);
				inSettings = false;
			}
		}
}

void SettingsMenu::draw()
{
	window.clear();
	window.draw(backGround.getSprite());
	window.draw(buttonSave.getSprite());
	window.draw(buttonBack.getSprite());
	window.draw(CheckboxFullScr.getSprite());
	window.draw(CheckboxVSync.getSprite());
	window.draw(maxFPS.getSprite());
	window.draw(windowSize.getSprite());
	window.draw(fps);
	window.draw(winSize);
	window.draw(opener.getSprite());
	window.display();
}
