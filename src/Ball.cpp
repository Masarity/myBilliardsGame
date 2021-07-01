#include "Ball.hpp"

Ball::Ball(sf::Color color, sf::Vector2f position, std::string kind, std::string id): _color(color),_kind(kind), _id(id), _position(position)
{
    //先画个黑八
    _ball.setFillColor(_color);
    _ball.setPosition(_position);
    _ball.setRadius(9);
    bool loadSuccess = font.loadFromFile("../resources/font/FreeSans.ttf");
    if (!loadSuccess)
    {
        std::cout << "load font failed!~" << std::endl;
    }
    _text.setFont(font);
    _text.setString(id);
    _text.setPosition(_position);
    _text.setFillColor(sf::Color::White);
    _text.setCharacterSize(10);

}

void Ball::update(sf::Time deltaTime)
{
    _position.x = _lineVelociy.x * deltaTime.asMilliseconds() +_ball.getPosition().x;
    _position.y = _lineVelociy.y * deltaTime.asMilliseconds() + _ball.getPosition().y;
    _ball.setPosition(_position);
    _text.setPosition(_position.x + 5, _position.y + 4);

}

Eigen::Vector2f Ball::getVelocity()
{
    return _lineV;
}

Eigen::Vector2f Ball::getPos()
{
    return Eigen::Vector2f(_position.x, _position.y);
}

sf::CircleShape& Ball::getBall()
{
    return _ball;
}

void Ball::changeVelocity(Eigen::Vector2f lineVelociy)
{
    _lineVelociy.x = lineVelociy(0, 0);
    _lineVelociy.y = lineVelociy(1, 0);
    _lineV = lineVelociy;
}

void Ball::changeVelocity(Eigen::Vector2f lineVelociy, std::string kind)
{
    _lineVelociy.x += lineVelociy(0, 0);
    _lineVelociy.y += lineVelociy(1, 0);
    _lineV += lineVelociy;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_ball, states);
    target.draw(_text, states);
}

