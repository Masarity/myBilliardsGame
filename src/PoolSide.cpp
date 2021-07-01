#include "PoolSide.hpp"

PoolSide::PoolSide(int i){}

Eigen::Vector2f& PoolSide::getNormalVector()
{
    return _normalVector;
}

sf::ConvexShape& PoolSide::getPoolSide()
{
    return _poolSide;
}

void PoolSide::addName(std::string name)
{
    _name = name;
}

void PoolSide::addPointCount(int number)
{
    _poolSide.setPointCount(number);
}

void PoolSide::addColor(sf::Color color)
{
    _poolSide.setFillColor(color);
}

void PoolSide::addPoint(int index, sf::Vector2f point)
{
    _poolSide.setPoint(index, point);
}

void PoolSide::addNormalVector(Eigen::Vector2f normalVector)
{
    _normalVector = normalVector;
}

void PoolSide::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_poolSide, states);
}
