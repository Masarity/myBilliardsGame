#include "Game.h"
#include <iostream>

Game::Game()
{
    settings.antialiasingLevel = 0;
    settings.stencilBits = 8;
    settings.depthBits = 24;
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    window.create(sf::VideoMode(800, 600), "2DbilliardsGame", sf::Style::Default, settings);
}

void Game::run(int frame_per_second)
{
    sf::Clock myClock;
    sf::Time deltaTime = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / (float)frame_per_second);
    while (window.isOpen())
    {
        processEvents();
        bool repaint = false;
        deltaTime += myClock.restart();
        while (deltaTime > timePerFrame)
        {
            deltaTime -= timePerFrame;
            repaint = true;
            update(timePerFrame);
        }
        if (repaint)
            render();
    }
}

void Game::processEvents()
{
   sf::Event event;
    while (window.pollEvent(event))
    {
        if ((event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
        {
            window.close();
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    myBilliardsBoard.update(deltaTime);
}

void Game::render()
{
    sf::Shader shader;
    window.clear();
    if (sf::Shader::isAvailable())
    {
        /* std::cout << "shader is available" << std::endl; */
        window.draw(myBilliardsBoard);
    }
    else 
    {
        std::cout << "shader is not availiable" << std::endl;
    }
    window.display();
}

