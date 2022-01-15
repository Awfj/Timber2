// Timber2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

enum class side { LEFT, RIGHT, NONE };

const int NUM_BRANCHES = 6;
side branchPositions[NUM_BRANCHES];

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber", Style::Fullscreen);

    Texture textureBackground;
    Sprite spriteBackground;
    textureBackground.loadFromFile("graphics/background.png");
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    Texture textureBee;
    Sprite spriteBee;
    textureBee.loadFromFile("graphics/bee.png");
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    bool beeActive = false;
    float beeSpeed = 0.2f;

    Texture textureTree;
    Sprite spriteTree;
    textureTree.loadFromFile("graphics/tree.png");
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    Texture texturePlayer;
    Sprite spritePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    side playerSide = side::LEFT;

    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);

    const float AXE_POSITIONI_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;
    spriteAxe.setPosition(AXE_POSITIONI_LEFT, 830);

    
    

    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    Text messageText;
    messageText.setFont(font);
    messageText.setString("Press Enter to start!");
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::White);

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score = 0");
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 20);

    // TIME BAR ------------------------------------------------------
    Clock clock;
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
    // -------------------------------------TIME BAR-------------------

    // SOUNDS --------------------------------------------------------
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);

    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);

    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);
    // /SOUNDS------------------------------------------------------------------

    bool acceptInput = false;
    bool paused = true;
    int score = 0;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !paused) {
                acceptInput = true;
                spriteAxe.setPosition(2000,
                    spriteAxe.getPosition().y);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        /*if (Keyboard::isKeyPressed(Keyboard::Return) ||
            Keyboard::isKeyPressed(Keyboard::Space)) {
            if (paused) {
                paused = false;
                acceptInput = true;
            }
            else {
                paused = true;
                acceptInput = false;
            }   
        }*/

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            acceptInput = true;
            timeRemaining = 6;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            paused = true;
            acceptInput = false;
        }

        if (acceptInput) {
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                playerSide = side::RIGHT;
                score++;
                timeRemaining += (2 / score) + 0.15;
                spritePlayer.setPosition(1200, 720);
                acceptInput = false;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                playerSide = side::LEFT;
                score++;
                timeRemaining += (2 / score) + 0.15;
                spritePlayer.setPosition(580, 720);
                acceptInput = false;
            }
        }

        window.clear();

        if (!paused) {
            Time dt = clock.restart();

            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond *
                timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f) {
                paused = true;
                messageText.setString("Out of time!");

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left +
                    textRect.width / 2.0f,
                    textRect.top +
                    textRect.height / 2.0f);
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        window.draw(spriteBackground);
        /*for (int i = 0; i < NUM_BRANCHES; i++) {
            window.draw(branches[i]);
        }*/
        window.draw(spriteTree);
        window.draw(spriteAxe);
        window.draw(spritePlayer);
        window.draw(spriteBee);
        window.draw(scoreText);
        window.draw(timeBar);

        if (paused) {
            window.draw(messageText);
        }

        window.display();
    }

    return 0;
}

void updateBranches(int seed) {
    for (int i = NUM_BRANCHES - 1; i > 0; i--) {
        branchPositions[i] = branchPositions[i - 1];
    }

    srand((int)time(0) + seed);
    int r = (rand() % 5);

    switch (r) {
    case 0:
        branchPositions[0] = side::LEFT;
        break;
    case 1:
        branchPositions[0] = side::RIGHT;
        break;
    default:
        branchPositions[0] = side::NONE;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
