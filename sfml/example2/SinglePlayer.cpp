#include "SinglePlayer.h"
#include <string>

//!Constructors

SinglePlayer::SinglePlayer(sf::RenderWindow& window, Opener& opener, int& menu) :
    window{ window }, ball(screenSize.x / 2, screenSize.y / 2, true, "images\\ball.png"),
    backGround("images\\bgSolo.png", screenSize.y, screenSize.x), ring(49, 4, 20),
    pause(screenSize.x / 2, screenSize.y / 2, 750, 198, 300),
    opener{ opener }, menu{ menu }
{
    std::string playerName;
    std::ifstream fromFile("CurrentPlayer.txt");
    fromFile >> playerName;
    fromFile.close();
    player = Player(playerName, 4.7, 15.8, 7, "images\\player1.png");
    ground = 880;
    restart();
}

SinglePlayer::~SinglePlayer()
{
}


//!Main

void SinglePlayer::gameStart()
{

    sf::Font font;
    font.loadFromFile("fonts\\ChixaDemiBold.ttf");
    timer.setFont(font);
    timer.setCharacterSize(fontSize);
    timer.setFillColor(sf::Color(0, 209, 255, 255));
    sf::Vector2f text_position(screenSize.x / 2 - 75, 227);
    timer.setPosition(text_position);

    playerScore.setFont(font);
    playerScore.setCharacterSize(fontSize+30);
    playerScore.setFillColor(sf::Color(74, 209, 151, 255));
    playerScore.setString(std::to_string(player.getScore()));
    playerScore.setPosition(960 - playerScore.getString().getSize() * 22, 80);

    sf::Clock circle;
    opener.setOpening(true);
    opener.setDirection(Direction::Top);

    while (isPlaying) {

        event(menu);

        float elapsed = circle.restart().asSeconds();

        update(elapsed);

        window.clear();

        draw();



    }
}

void SinglePlayer::PlayerMove(const float& elapsed)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        if (player.getPosition().x > player.getWidth() / 2)
        {
            player.move(-player.getSpeed() * elapsed * 144, 0);
            player.setDirection(Left);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (player.getPosition().x < screenSize.x - player.getWidth() / 2)
        {
            player.move(player.getSpeed() * elapsed * 144, 0);
            player.setDirection(Right);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        if (player.OnGround(ground))
            player.jump();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    {
        if (playerHaveBall)
        {
            this->setBallRotation(elapsed * 0.3);
            playerHaveBall = false;
            throwBallShort(player.getDirection(), player.getThrowStrength());
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
    {
        if (playerHaveBall)
        {
            this->setBallRotation(elapsed * 0.3);
            playerHaveBall = false;
            throwBallLong(player.getDirection(), player.getThrowStrength());
        }
    }

    player.move(0, player.getYSpeed() * elapsed * 144);

    if (!player.OnGround(ground))
    {
        player.falling(elapsed);
    }
    else
    {
        player.setYSpeed(0);
        player.setPosition(player.getPosition().x, ground - player.getHeight() / 2);
    }
}

void SinglePlayer::ballMove(const float& elapsed)
{
    if (!playerHaveBall) {

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

        switch (player.getDirection())
        {
        case Right:
            ball.setPosition(player.getPosition().x + player.getWidth() / 3 * 2, player.getPosition().y - player.getHeight() / 3);
            break;

        case Left:
            ball.setPosition(player.getPosition().x - player.getWidth() / 3 * 2, player.getPosition().y - player.getHeight() / 3);
            break;

        }
    }
}

void SinglePlayer::draw()
{

    window.draw(backGround.getSprite());


    window.draw(timer);

    window.draw(ball.getSprite());
    window.draw(ring.getSprite());
    window.draw(playerScore);
    window.draw(player.getSprite());

    if (pause.onPause()) {
        drawPause();
    }
    window.draw(opener.getSprite());
    window.display();
}

void SinglePlayer::drawPause()
{
    window.draw(pause.pauseBG.getSprite());
    window.draw(pause.buttonContinue.getSprite());
    window.draw(pause.buttonExit.getSprite());
    window.draw(pause.buttonToMenu.getSprite());
}

void SinglePlayer::update(const float& elapsed)
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

            timer.setString(minutes + ":" + seconds);
            PlayerMove(elapsed);
            ballMove(elapsed);
            if (goal && endOfRound.getElapsedTime().asSeconds() >= 1)
            {
                restart();
                goal = false;
            }
            if (timeIsOut()) 
            {
                writeScore(player);
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
            if (opener.getPosition().y > 1080 || opener.getPosition().y < 0 || opener.getPosition().x < 0 || opener.getPosition().x > 1920)
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

void SinglePlayer::event(int& menu)
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
                if (player.getGlobalBounds().intersects(ball.getGlobalBounds()))
                {
                    playerHaveBall = true;
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

void SinglePlayer::gameGoal()
{

    player.setScore(player.getScore() + 1);
    playerScore.setString(std::to_string(player.getScore()));
    playerScore.setPosition(960 - playerScore.getString().getSize() * 22, 80);
    this->goal = true;
    endOfRound.restart();
}

void SinglePlayer::setFontSize(const int& fontSize)
{
    this->fontSize = fontSize;
}

void SinglePlayer::restart()
{
    ball.setPosition(screenSize.x / 2, screenSize.y*2 / 3);
    ball.setXSpeed(0);
    ball.setYSpeed(0);
    playerHaveBall = false;
    ring.setPosition(sf::Vector2f(rand() % 1520 + 200, rand() % 50 + 375));



    player.setPosition(screenSize.x / 2, ground - player.getHeight() / 2);

    backGround.getSprite().setPosition(screenSize.x / 2, screenSize.y / 2);
}

void SinglePlayer::throwBallShort(Direction direction, const float& throwStrength)
{
    switch (direction)
    {
    case Right:
        ball.setXSpeed(throwStrength);
        ball.setYSpeed(-throwStrength * 1.5);
        break;
    case Left:
        ball.setXSpeed(-throwStrength);
        ball.setYSpeed(-throwStrength * 1.5);
        break;
    }
}

void SinglePlayer::throwBallLong(Direction direction, const float& throwStrength)
{
    switch (direction)
    {
    case Right:
        ball.setXSpeed(throwStrength * 1.5f);
        ball.setYSpeed(-throwStrength * 1.5f);
        break;
    case Left:
        ball.setXSpeed(-throwStrength * 1.5f);
        ball.setYSpeed(-throwStrength * 1.5f);
        break;
    }
}

void SinglePlayer::setBallRotation(const float& elapsed)
{
    ball.setRotationSpeed((rand() % 51 + 100) * elapsed * ball.getXSpeed());
}

void SinglePlayer::ballBounceFromRing()
{
    if (ball.getSize().x / 2 + ring.getRingThickness() >= sqrt(pow(ball.getPosition().x - ring.getLeftCirclePosition().x, 2) + pow(ball.getPosition().y - ring.getLeftCirclePosition().y, 2)))
    {
        ball.bounce(ring.getLeftSprite());
    }
    if (ball.getSize().x / 2 + ring.getRingThickness() >= sqrt(pow(ball.getPosition().x - ring.getRightCirclePosition().x, 2) + pow(ball.getPosition().y - ring.getRightCirclePosition().y, 2)))
    {
        ball.bounce(ring.getRightSprite());
    }
}

void SinglePlayer::ballBounceFromWall()
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

void SinglePlayer::writeScore(Player& player)
{
    std::vector<std::string> names;
    std::vector<int> scores;
    std::string name;
    int score;
    std::ifstream fromFile("scores.txt");
    for (int i = 0; i < 10; i++)
    {
        if (fromFile.eof() || !fromFile)
        {
            names.push_back("No_Data");
            scores.push_back(0);
        }
        else
        {
            fromFile >> name;
            fromFile >> score;
            names.push_back(name);
            scores.push_back(score);
        }
    }
    fromFile.close();
    int position = -1;
    for (int i = 0; i < 10; ++i) {
        if (scores[i] < player.getScore())
        {
            position = i;
            break;
        }
    }
    if (position != -1) 
    {
        for (int i = 9; i > position; --i) 
        {
            names[i] = names[i - 1];
            scores[i] = scores[i - 1];
        }
        names[position] = player.getName();
        scores[position] = player.getScore();
        std::ofstream toFile("scores.txt");
        for (int i = 0; i < 10; i++) 
        {
            toFile << names[i] << " " << scores[i] << std::endl;
        }
    }
}

//!Gets

int SinglePlayer::getFontSize()
{
    return this->fontSize;
}

sf::Text SinglePlayer::printScore(Player& player, const float& x, const float& y)
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

bool SinglePlayer::BallInRing()
{
    if (ring.getLineGlobalBounds().contains(ball.getPosition()))
        return true;
    return false;
}

bool SinglePlayer::timeIsOut()
{
    if (timeNotOut) {
        timeNotOut = time > 0 ? true : false;
        return time > 0 ? false : true;
    }
    else return false;
}
