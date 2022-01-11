// Timber2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
//#include <sstream>
#include <SFML/Graphics.hpp>
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
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            paused = true;
            acceptInput = false;
        }

        if (acceptInput) {
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                playerSide = side::RIGHT;
                spritePlayer.setPosition(1200, 720);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                playerSide = side::LEFT;
                spritePlayer.setPosition(580, 720);
            }
        }

        window.clear();

        if (!paused) {

        }

        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spriteAxe);
        window.draw(spritePlayer);
        window.draw(scoreText);

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
