#include "SinglePlayer.h"
#include "GameSettings.h"
#include "GameWindow.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
int main()
{
    GameSettings settings;

    readSettings(settings);

    sf::RenderWindow window;
   
    if (settings.fullScreen) window.create(sf::VideoMode(1920, 1080), "game", sf::Style::None);
    else window.create(sf::VideoMode(settings.windowWidth, settings.windowHeight), "game", sf::Style::None);

    if (settings.vSync) window.setVerticalSyncEnabled(true);
    else window.setFramerateLimit(settings.maxFPS);

    sf::View view(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080));
    window.setView(view);
    if (settings.fullScreen) window.setPosition(sf::Vector2i(view.getCenter().x - 1920 / 2, view.getCenter().y - 1080 / 2));
    else window.setPosition(sf::Vector2i(view.getCenter().x-settings.windowWidth/2, view.getCenter().y - settings.windowHeight / 2));
    Opener opener;
    opener.setPosition(-10000,-10000);
    int curentMenu = Menu::mainMenu;
    while (window.isOpen())
    {
        switch (curentMenu) {
        case Menu::mainMenu:
        {
            MainMenu menuMain(window, opener, curentMenu);
            menuMain.open();
            break;
        }

        case Menu::game:
        {
            GameWindow game(window, opener, curentMenu);
            game.gameStart();
            break;
        }

        case Menu::settings:
        {
            SettingsMenu settingsMenu(window, opener, curentMenu);
            settingsMenu.open();
            break;
        }

        case Menu::singlePlayer: {
            SinglePlayer sp(window, opener, curentMenu);
            sp.gameStart();
            break;
        }

        }
    }
    return 0;
}