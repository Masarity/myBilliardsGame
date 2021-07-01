#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include "Ball.hpp"
#include "CreateStaticElements.hpp"
#include <Eigen/Core>
#include "Physics.hpp"

class Board: public sf::Drawable
{
public:
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    Board();

    template<typename ... Args>
        void setPosition(Args&& ... args)
        {
            _outBoard.setPosition(std::forward<Args>(args)...);
        }
    void update(sf::Time deltaTime);
    Ball& getBlackBall();

private:
    //board attributes
    sf::RectangleShape _outBoard;
    std::vector<sf::CircleShape> _ballHoles;
    struct ballHolesPos
    {
        float x;
        float y;
    } _ballHolesPosList[6];
    sf::RectangleShape _startLine;
    sf::CircleShape _centerPoint;
    sf::CircleShape _initPoint;
    /* std::vector<sf::ConvexShape> _poolSides; */
    CreateStaticElements _staticCreator;
    // 摩擦系数friction
    float friction = 0.f;

    //ball attributes
    Ball _blackBall;
    Ball _whiteBall;
    std::stack<Ball> eightBalls;

    Physics _myPhyics;
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

