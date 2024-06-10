#pragma once
#include "Opener.h"
#include "Player.h"
#include "Ball.h"
#include "Ring.h"
#include "Pause.h"
#include "Menu.h"
#include <array>
const int playersAmount = 2;
class GameWindow : sf::RenderWindow
{
private:
	//!window
	sf::Vector2f screenSize{1920,1080};
	sf::RenderWindow& window;
	float ground;
	int fontSize = 70;
	int& menu;

	//!objects
	MySprite backGround;
	std::array<Player,playersAmount> player;
	Ball ball;
	Ring leftRing;
	Ring rightRing;
	std::array<sf::Text, playersAmount> playerScore;
	sf::Text timer;
	Pause pause;
	Opener& opener;
	
	//!game variables
	bool isPlaying = true;
	std::array<bool,2> playerHaveBall;
	float time = 300;
	bool goal = false;
	sf::Clock endOfRound;
	bool timeNotOut = true;


public:

	//!Constructors
	
	GameWindow(sf::RenderWindow& window, Opener& opener, int& menu);

	~GameWindow();

	//!Main

	void gameStart();
	
	void firstPlayerMove(const float& elapsed);
	
	void secondPlayerMove(const float& elapsed);
	
	void ballMove(const float& elapsed);
	
	void draw();

	void drawPause();

	void update(const float& elapsed);

	void event(int& menu);
	
	//!Sets

	void gameGoal();

	void setFontSize(const int &fontSize);

	void restart();

	void throwBallShort(Direction direction, const float& throwStrength);

	void throwBallLong(Direction direction, const float& throwStrength);
	
	void setBallRotation(const float& elapsed);
	
	void ballBounceFromRing();
	
	void ballBounceFromWall();
	
	//!Gets

	int getFontSize();

	sf::Text printScore(Player& player,const float &x,const float &y);

	bool someoneHaveBall();

	bool BallInRing();

	bool timeIsOut();
};

