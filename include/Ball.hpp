#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <Eigen/Core>

class Ball: public sf::Drawable
{
public:
    /* Ball(const Ball&) = delete; */
    /* Ball& operator=(const Ball&) = delete; */
    Ball(sf::Color color, sf::Vector2f positon, std::string kind, std::string id);

    template<typename ... Args>
        void setPosition(Args&& ... args)
        {
        }
    void update(sf::Time deltaTime);//, sf::RectangleShape poolSide){}
    Eigen::Vector2f getVelocity();
    sf::CircleShape& getBall();
    Eigen::Vector2f getPos();
    void changeVelocity(Eigen::Vector2f);
    void changeVelocity(Eigen::Vector2f, std::string);


public:
    sf::Font font;

private:
    sf::CircleShape _ball;
    sf::Text _text;
    sf::Color _color;
    std::string _kind;
    std::string _id;
    sf::Vector2f _position;
    sf::Vector2f _lineVelociy = sf::Vector2f(0.f, 0.f);
    Eigen::Vector2f _lineV = Eigen::Vector2f(0.f, 0.f);
    float _rotateVelocity = 0;
    float _mass = 50;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};

