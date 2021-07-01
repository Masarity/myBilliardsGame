#include "CreateStaticElements.hpp"
#include "PoolSide.hpp"
#include <Eigen/Core>

#define POOLSIDE_COLOR sf::Color(255, 192, 203)

CreateStaticElements::CreateStaticElements(){}

void CreateStaticElements::createPoolSides()
{
    //库边绘制
    PoolSide poolSide(7);
    poolSide.addPointCount(4);
    //200, 100, 50
    poolSide.addColor(POOLSIDE_COLOR);
    for (int i=0; i<380.f; i+=375.f)
    {
        poolSide.addPoint(0, sf::Vector2f(40.f + i, 20.f));
        poolSide.addPoint(1, sf::Vector2f(386.f + i, 20.f));
        poolSide.addPoint(2, sf::Vector2f(381.f + i, 25.f));
        poolSide.addPoint(3, sf::Vector2f(45.f + i, 25.f));
        poolSide.addNormalVector(Eigen::Vector2f(0.f, 1.f));
        _poolSides.push_back(poolSide);
        poolSide.addPoint(0, sf::Vector2f(40.f + i, 400.f - 20.f));
        poolSide.addPoint(1, sf::Vector2f(386.f + i, 400.f - 20.f));
        poolSide.addPoint(2, sf::Vector2f(381.f + i, 400.f - 25.f));
        poolSide.addPoint(3, sf::Vector2f(45.f + i, 400.f - 25.f));
        poolSide.addNormalVector(Eigen::Vector2f(0.f, -1.f));
        _poolSides.push_back(poolSide);
    }
    poolSide.addPoint(0, sf::Vector2f(20.f, 40.f));
    poolSide.addPoint(1, sf::Vector2f(20.f, 362.f));
    poolSide.addPoint(2, sf::Vector2f(25.f, 357.f));
    poolSide.addPoint(3, sf::Vector2f(25.f, 45.f));
    poolSide.addNormalVector(Eigen::Vector2f(-1.f, 0.f));
    _poolSides.push_back(poolSide);
    poolSide.addPoint(0, sf::Vector2f(800.f - 20.f, 40.f));
    poolSide.addPoint(1, sf::Vector2f(800.f - 20.f, 362.f));
    poolSide.addPoint(2, sf::Vector2f(800.f - 25.f, 357.f));
    poolSide.addPoint(3, sf::Vector2f(800.f - 25.f, 45.f));
    poolSide.addNormalVector(Eigen::Vector2f(1.f, 0.f));
    _poolSides.push_back(poolSide);
}

std::vector<PoolSide>& CreateStaticElements::getPoolSides()
{
    return _poolSides;
}

void CreateStaticElements::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto iter = _poolSides.begin(); iter != _poolSides.end(); iter++)
    {
        target.draw(*iter, states);
    }
}
