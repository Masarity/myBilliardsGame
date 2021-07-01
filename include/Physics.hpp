#pragma once
#include <Eigen/Core>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "PoolSide.hpp"

class Physics
{
public:
    Physics();
    ~Physics();
    void collision(Ball& ball, PoolSide& poolSide);
    void collision(Ball& ball1, Ball& ball2);

private:

};

