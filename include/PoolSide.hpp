#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Eigen/Core>

class PoolSide: public sf::Drawable
{
public:
    /* PoolSide(const PoolSide&) = delete; */
    /* PoolSide& operator=(const PoolSide&) = delete; */
    PoolSide(int);
    void addPointCount(int);
    void addPoint(int, sf::Vector2f);
    void addColor(sf::Color);
    void addName(std::string);
    void addNormalVector(Eigen::Vector2f);
    Eigen::Vector2f& getNormalVector();
    sf::ConvexShape& getPoolSide();
    template<typename ... Args>
        void setPosition(Args&& ... args)
        {
            _poolSide.setPosition(std::forward<Args>(args)...);
        }

private:
    sf::ConvexShape _poolSide;
    Eigen::Vector2f _normalVector;
    std::string _name;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

