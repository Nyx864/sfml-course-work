#include "GameWindow.h"
#include <string>

//!Constructors

GameWindow::GameWindow(sf::RenderWindow& window,Opener& opener, int& menu):
    window{ window }, ball(screenSize.x / 2, screenSize.y / 2, true, "images\\ball.png"), 
    backGround("images\\bgDuo.png", screenSize.y, screenSize.x), leftRing(49, 4, 20), 
    rightRing(50, 4, 20), pause(screenSize.x/2,screenSize.y/2, 750, 198, 300),
    opener{ opener }, menu{menu}
{
    player[0] = Player("", 4.7, 15.8, 7, "images\\player1.png");
    player[1] = Player("2", 4, 17, 7, "images\\player2.png");
    ground = 880;
    restart();
}

GameWindow::~GameWindow()
{
}

//!Main

void GameWindow::gameStart()
{

    sf::Font font;
    font.loadFromFile("fonts\\ChixaDemiBold.ttf");
    timer.setFont(font);
    timer.setCharacterSize(fontSize);
    timer.setFillColor(sf::Color(0,209,255,255));
    sf::Vector2f text_position(screenSize.x / 2-75, 227);
    timer.setPosition(text_position);
    std::string minutes;
    if (int(time) / 60 > 9)minutes = std::to_string(int(time) / 60);
    else minutes = "0" + std::to_string(int(time) / 60);

    std::string seconds;
    if (int(time) % 60 > 9)seconds = std::to_string(int(time) % 60);
    else seconds = "0" + std::to_string(int(time) % 60);

    timer.setString(minutes + ":" + seconds);

    playerScore[0].setFont(font);
    playerScore[0].setCharacterSize(fontSize+30);
    playerScore[0].setFillColor(sf::Color(74,209,151,255));
    playerScore[0].setString(std::to_string(player[0].getScore()));
    playerScore[0].setPosition(822 - playerScore[0].getString().getSize() * 22, 80);

    playerScore[1].setFont(font);
    playerScore[1].setCharacterSize(fontSize+30);
    playerScore[1].setFillColor(sf::Color(188, 39, 39, 255));
    playerScore[1].setString(std::to_string(player[1].getScore()));
    playerScore[1].setPosition(1100 - playerScore[1].getString().getSize() * 22, 80);


    sf::Clock circle;
    opener.setOpening(true);
    opener.setDirection(Direction::Top);

    while (isPlaying) {
        
        event(menu);

        float elapsed = circle.restart().asSeconds();

        update(elapsed);

        draw();
    }
}

void GameWindow::firstPlayerMove(const float& elapsed)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        if (player[0].getPosition().x > player[1].getWidth() / 2)
        {
            player[0].move(-player[0].getSpeed() * elapsed * 144, 0);
            player[0].setDirection(Left);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) 
    {
        if (player[0].getPosition().x < screenSize.x - player[0].getWidth() / 2)
        {
            player[0].move(player[0].getSpeed() * elapsed * 144, 0);
            player[0].setDirection(Right);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        if (player[0].OnGround(ground))
            player[0].jump();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) 
    {
        if (playerHaveBall[0]) 
        {
            this->setBallRotation(elapsed * 0.3);
            playerHaveBall[0] = false;
            throwBallShort(player[0].getDirection(), player[0].getThrowStrength());
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
    {
        if (playerHaveBall[0])
        {
            this->setBallRotation(elapsed * 0.3);
            playerHaveBall[0] = false;
            throwBallLong(player[0].getDirection(), player[0].getThrowStrength());
        }
    }

    player[0].move(0, player[0].getYSpeed() * elapsed * 144);

    if (!player[0].OnGround(ground))
    {
        player[0].falling(elapsed);
    }
    else
    {
        player[0].setYSpeed(0);
        player[0].setPosition(player[0].getPosition().x, ground - player[0].getHeight()/2);
    }
}

void GameWindow::secondPlayerMove(const float &elapsed)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4)) 
    {
        if (player[1].getPosition().x > player[1].getWidth() / 2)
        {
            player[1].move(-player[1].getSpeed() * elapsed * 144, 0);
            player[1].setDirection(Left);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6))
    {
        if (player[1].getPosition().x < screenSize.x - player[1].getWidth() / 2)
        {
            player[1].move(player[1].getSpeed() * elapsed * 144, 0);
            player[1].setDirection(Right);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8))
    {
        if (player[1].OnGround(ground))
            player[1].jump();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad9))
    {
        if (playerHaveBall[1])
        {
            this->setBallRotation(elapsed * 0.3);
            playerHaveBall[1] = false;
            throwBallShort(player[1].getDirection(), player[1].getThrowStrength());
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad7))
    {
        if (playerHaveBall[1])
        {
            this->setBallRotation(elapsed * 0.3);
            playerHaveBall[1] = false;
            throwBallLong(player[1].getDirection(), player[1].getThrowStrength());
        }
    }

    player[1].move(0, player[1].getYSpeed() * elapsed * 144);

    if (!player[1].OnGround(ground))
    {
        player[1].falling(elapsed);
    }
    else
    {
        player[1].setYSpeed(0);
        player[1].setPosition(player[1].getPosition().x, ground - player[1].getHeight()/2);
    }
}

void GameWindow::ballMove(const float& elapsed)
{
    if (!someoneHaveBall()) {

        ball.rotate();
        ball.move(0, ball.getYSpeed() * elapsed * 100);


        if (ball.getXSpeed() != 0) {
            ball.move(ball.getXSpeed() * elapsed * 100, 0);
            if (ball.getXSpeed() > 0)
                ball.setXSpeed(ball.getXSpeed() - 2 * elapsed);
            if (ball.getXSpeed() < 0)
                ball.setXSpeed(ball.getXSpeed() + 2 * elapsed);
            if (fabs(ball.getXSpeed()) < 0.3)
                ball.setXSpeed(0);
        }
        if (!ball.OnGround(ground))
        {
            ball.falling(elapsed);
            ballBounceFromRing();
            if (BallInRing() && !goal)
            {
                endOfRound.restart();
                gameGoal();
            }
            ballBounceFromWall();
        }
        else
        {
            this->setBallRotation(elapsed);
            if (std::fabs(ball.getYSpeed()) < elapsed * 166)
                ball.setYSpeed(0);
            ball.bounce(Direction::Bottom);
            ball.setPosition(ball.getPosition().x, ground - ball.getSize().y / 2);
        }
    }

    else
    {
        if (playerHaveBall[0])
        {
            switch (player[0].getDirection())
            {
            case Right:
                ball.setPosition(player[0].getPosition().x + player[0].getWidth() / 3 * 2, player[0].getPosition().y - player[0].getHeight() / 3);
                break;

            case Left:
                ball.setPosition(player[0].getPosition().x - player[0].getWidth() / 3 * 2, player[0].getPosition().y - player[0].getHeight() / 3);
                break;
            }
        }
        else
        {
            switch (player[1].getDirection())
            {
            case Right:
                ball.setPosition(player[1].getPosition().x + player[1].getWidth() / 3 * 2, player[1].getPosition().y - player[1].getHeight() / 3);
                break;

            case Left:
                ball.setPosition(player[1].getPosition().x - player[1].getWidth() / 3 * 2, player[1].getPosition().y - player[1].getHeight() / 3);
                break;
            }
        }
    }
}

void GameWindow::draw()
{
    window.clear();
    window.draw(backGround.getSprite());
   

    window.draw(timer);

    window.draw(ball.getSprite());
    for (int i=0;i<playersAmount;++i)
    {
        window.draw(playerScore[i]);
        window.draw(player[i].getSprite());
    }
    window.draw(leftRing.getSprite());
    window.draw(rightRing.getSprite());
    if (pause.onPause()) {
        drawPause();
    }
    window.draw(opener.getSprite());
    window.display();
}

void GameWindow::drawPause()
{
    window.draw(pause.pauseBG.getSprite());
    window.draw(pause.buttonContinue.getSprite());
    window.draw(pause.buttonExit.getSprite());
    window.draw(pause.buttonToMenu.getSprite());
}

void GameWindow::update(const float& elapsed)
{
    if (!opener.isOpening() && !opener.isClosing()) {
        if (!pause.onPause()) {
            time -= elapsed;
            std::string minutes;
            if (int(time) / 60 > 9)minutes = std::to_string(int(time) / 60);
            else minutes = "0" + std::to_string(int(time) / 60);

            std::string seconds;
            if (int(time) % 60 > 9)seconds = std::to_string(int(time) % 60);
            else seconds = "0" + std::to_string(int(time) % 60);

            timer.setString(minutes+":"+ seconds);
            firstPlayerMove(elapsed);
            secondPlayerMove(elapsed);
            ballMove(elapsed);
            if (goal && endOfRound.getElapsedTime().asSeconds() >= 1)
            {
                restart();
                goal = false;
            }
            if (timeIsOut())
            {
                opener.setOpening(false);
                opener.setClosing(Direction::Top, true);
            }
        }
        if (pause.onPause()) {
            pause.setPosition(960, 540);
            pause.updateButtons();
        }
        else pause.setPosition(1920, 0);
    }
    else 
    {
        if (opener.isOpening()) {
            if (opener.getPosition().y < 4580 && opener.getPosition().y > -5000 && opener.getPosition().x > -5000 && opener.getPosition().x < 6920)
            {
                opener.move(elapsed);
            }
            else
            {
                opener.setOpening(false);
            }
        }
        else 
        {
            if (opener.getPosition().y > 1080 || opener.getPosition().y < 0  || opener.getPosition().x < 0 || opener.getPosition().x > 1920)
            {
                opener.move(elapsed);
            }
            else
            {
                opener.setClosing(false);
                opener.setOpening(true);
                opener.setDirection(Direction::Top);
                isPlaying = false;
                menu = Menu::mainMenu;
            }
        }
    }
}

void GameWindow::event(int& menu)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Key::Escape)
                if (pause.onPause()) pause.setOnPause(false);
                else pause.setOnPause(true);

            if (event.key.code == sf::Keyboard::Key::Space)
                if (player[0].getGlobalBounds().intersects(ball.getGlobalBounds()))
                {
                    playerHaveBall[1] = false;
                    playerHaveBall[0] = true;
                }

            if (event.key.code == sf::Keyboard::Key::Numpad0)
                if (player[1].getGlobalBounds().intersects(ball.getGlobalBounds()))
                {
                    playerHaveBall[0] = false;
                    playerHaveBall[1] = true;
                }
            break;
        case sf::Event::MouseButtonPressed:
            if (pause.buttonContinue.mouseOnButton())
            {
                pause.setOnPause(false);
            }

            if (pause.buttonToMenu.mouseOnButton())
            {
                opener.setOpening(false);
                opener.setClosing(Direction::Top, true);
            }

            if (pause.buttonExit.mouseOnButton())
            {
                isPlaying = false;
                window.close();
            }
            break;
        }
    }
}

//!Sets
 
void GameWindow::gameGoal()
{
    if (ball.getPosition().x > screenSize.x / 2) {
        player[0].setScore(player[0].getScore() + 1);
        playerScore[0].setString(std::to_string(player[0].getScore()));
        playerScore[0].setPosition(822 - playerScore[0].getString().getSize() * 22, 80);
    }
    else {
        player[1].setScore(player[1].getScore() + 1);
        playerScore[1].setString(std::to_string(player[1].getScore()));
        playerScore[1].setPosition(1100 - playerScore[1].getString().getSize() * 22, 80);
    }
    this->goal = true;
    endOfRound.restart();
}

void GameWindow::setFontSize(const int &fontSize)
{
    this->fontSize = fontSize;
}

void GameWindow::restart()
{
    playerHaveBall[0] = false;
    playerHaveBall[1] = false;
    ball.setXSpeed(0);
        ball.setYSpeed(0);
        ball.setPosition(screenSize.x / 2, screenSize.y / 2);
    rightRing.setPosition(sf::Vector2f(1720, 410));
    leftRing.setPosition(sf::Vector2f(200, 410));

    player[0].setDirection(Right);
    player[1].setDirection(Left);

    player[0].setPosition(screenSize.x / 16, ground - player[0].getHeight() / 2);
    player[1].setPosition(screenSize.x * 15 / 16, ground - player[1].getHeight() / 2);

    playerHaveBall[0] = false;
    playerHaveBall[0] = false;

    backGround.getSprite().setPosition(screenSize.x / 2, screenSize.y / 2);
}

void GameWindow::throwBallShort(Direction direction,const float& throwStrength)
{
    switch (direction)
    {
    case Right:
        ball.setXSpeed(throwStrength);
        ball.setYSpeed(-throwStrength*1.5);
        break;
    case Left:
        ball.setXSpeed(-throwStrength);
        ball.setYSpeed(-throwStrength*1.5);
        break;
    }
}

void GameWindow::throwBallLong(Direction direction, const float& throwStrength)
{
    switch (direction)
    {
    case Right:
        ball.setXSpeed(throwStrength*1.5f);
        ball.setYSpeed(-throwStrength*1.5f);
        break;
    case Left:
        ball.setXSpeed(-throwStrength*1.5f);
        ball.setYSpeed(-throwStrength*1.5f);
        break;
    }
}

void GameWindow::setBallRotation(const float& elapsed)
{
        ball.setRotationSpeed((rand() % 51+100)*elapsed*ball.getXSpeed());
}

void GameWindow::ballBounceFromRing()
{
    if (ball.getSize().x / 2 + leftRing.getRingThickness() >= sqrt(pow(ball.getPosition().x - leftRing.getLeftCirclePosition().x, 2) + pow(ball.getPosition().y - leftRing.getLeftCirclePosition().y, 2)))
    {
        ball.bounce(leftRing.getLeftSprite());
    }
    if (ball.getSize().x / 2 + leftRing.getRingThickness() >= sqrt(pow(ball.getPosition().x - leftRing.getRightCirclePosition().x, 2) + pow(ball.getPosition().y - leftRing.getRightCirclePosition().y, 2)))
    {
        ball.bounce(leftRing.getRightSprite());
    }
    if (ball.getSize().x / 2 + rightRing.getRingThickness() >= sqrt(pow(ball.getPosition().x - rightRing.getLeftCirclePosition().x, 2) + pow(ball.getPosition().y - rightRing.getLeftCirclePosition().y, 2)))
    {
        ball.bounce(rightRing.getLeftSprite());
    }
    if (ball.getSize().x / 2 + rightRing.getRingThickness() >= sqrt(pow(ball.getPosition().x - rightRing.getRightCirclePosition().x, 2) + pow(ball.getPosition().y - rightRing.getRightCirclePosition().y, 2)))
    {
        ball.bounce(rightRing.getRightSprite());
    }
}

void GameWindow::ballBounceFromWall()
{
    if (ball.getPosition().x <= ball.getSize().x / 2)
    {
        ball.bounce(Left);
        ball.setPosition(ball.getSize().x / 2, ball.getPosition().y);
    }

    if (ball.getPosition().x >= screenSize.x - ball.getSize().x / 2)
    {
        ball.bounce(Right);
        ball.setPosition(screenSize.x - ball.getSize().x / 2, ball.getPosition().y);
    }
}

//!Gets

int GameWindow::getFontSize()
{
    return this->fontSize;
}

sf::Text GameWindow::printScore(Player& player,const float &x,const float &y)
{
    sf::Font font;
    font.loadFromFile("COOPBL.ttf");
    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(fontSize);
    score.setString(std::to_string(player.getScore()));
    score.setPosition(x, y);
    return score;
}

bool GameWindow::someoneHaveBall()
{
    for (auto p : playerHaveBall)
        if (p)
            return true;
    return false;
}

bool GameWindow::BallInRing()
{
    if (leftRing.getLineGlobalBounds().contains(ball.getPosition()))
        return true;
    if (rightRing.getLineGlobalBounds().contains(ball.getPosition()))
        return true;
    return false;
}

bool GameWindow::timeIsOut()
{
    if (timeNotOut) {
        timeNotOut = time > 0 ? true : false;
        return time > 0 ? false : true;
    }
    else return false;
}
