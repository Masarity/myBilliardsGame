#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "PoolSide.hpp"

class CreateStaticElements: public sf::Drawable
{
public:
    CreateStaticElements(const CreateStaticElements&) = delete;
    CreateStaticElements& operator=(const CreateStaticElements&) = delete;
    CreateStaticElements();
    std::vector<PoolSide>& getPoolSides();
    void createPoolSides();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<PoolSide> _poolSides;

};

