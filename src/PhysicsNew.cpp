#include "Physics.hpp"
#include <math.h>

Physics::Physics(){}

Physics::~Physics(){}

float getAlpha(Eigen::Vector2f a, Eigen::Vector2f b)
{
    if (a.norm() * b.norm() < 1e-6)
        return 0.f;
    float ret = acos(a.dot(b.transpose()) / (a.norm() * b.norm()));
    /* std::cout << "a.dot(b.transpose()):\t" << a.dot(b.transpose()) */
    /*     << "\na.norm() * b.norm():\t" << a.norm() * b.norm() << std::endl; */
    return !isnan(ret) ? ret : 0.f;
    /* return ret; */
}

void setNewVelocity(Eigen::Vector2f& base, float baseFlag, float flag, Eigen::Vector2f& ballLineVelocity, Ball& ball)
{
    float alpha;
    alpha = acos(ballLineVelocity.dot(base.transpose()) / ballLineVelocity.norm());
    Eigen::Matrix2f rotateMatrix;
    rotateMatrix << cos(alpha),         flag * baseFlag * sin(alpha),
                    (-1) * flag * baseFlag * sin(alpha),  cos(alpha);
    Eigen::Vector2f newVelocity;
    newVelocity = ballLineVelocity.norm() * (base.transpose() * rotateMatrix);
    ball.changeVelocity(newVelocity);

    }

void Physics::collision(Ball& ball, PoolSide& poolSide)
{
    sf::CircleShape targetBall = ball.getBall();
    sf::FloatRect ballBox = targetBall.getGlobalBounds();
    sf::ConvexShape targetPoolSide = poolSide.getPoolSide();
    sf::FloatRect poolSideBox = targetPoolSide.getGlobalBounds();
    if (poolSideBox.intersects(ballBox))
    {
        Eigen::Vector2f ballLineVelocity = ball.getVelocity();
        Eigen::Vector2f normalVector = poolSide.getNormalVector();
        float flagy = normalVector(1, 0), flagx = normalVector(0, 0);
        float basex = 0.f, basey = 0.f;
        Eigen::Vector2f base;
        if (normalVector(0, 0) == 0.f)
        {
            if (ballLineVelocity(0, 0) < 0) basex = -1.f;
            else basex = 1.f;
            base << basex, basey;
            setNewVelocity(base, basex, flagy, ballLineVelocity, ball);
        }
        else if (normalVector(1, 0) == 0.f)
        {
            if (ballLineVelocity(1, 0) < 0) basey = -1.f;
            else basey = 1.f;
            base << basex, basey;
            setNewVelocity(base, basey, flagx, ballLineVelocity, ball);
        }
    }
}

float myAcos(float x, float y)
{
    if (!x && y > 0) return 90;
    else if (!x && y < 0) return 270;
    else if (!x && x == y) return 0;
    if (y >= 0)
    {
        return acos(1/x) * 180 / acos(-1);
    }
    else 
    {
        return (acos(1/x) / acos(-1) + 1) * 180;
    }
}

int velocityDirection(Eigen::Vector2f lv, Eigen::Vector2f ls)
{
    float alphav = myAcos(lv(0, 0), lv(1, 0)), alphas = myAcos(ls(0, 0), ls(1, 0));
    if (alphav - alphas >= 0 || (alphav - alphas > -90 && alphav - alphas <= -270))
        return 1;
    else return -1;
}

void Physics::collision(Ball& ball1, Ball& ball2)
{
    sf::FloatRect ball1Box = ball1.getBall().getGlobalBounds();
    sf::FloatRect ball2Box = ball2.getBall().getGlobalBounds();
    if (ball1Box.intersects(ball2Box))
    {
        Eigen::Vector2f l12 = ball2.getPos() - ball1.getPos();
        l12.normalize();
        Eigen::Vector2f l21 = ball1.getPos() - ball2.getPos();
        l21.normalize();

        Eigen::Vector2f unitBall1Velocity = ball1.getVelocity();
        Eigen::Vector2f unitBall2Velocity = ball2.getVelocity();
        float ball1V = unitBall1Velocity.norm(), ball2V = unitBall2Velocity.norm();
        unitBall1Velocity.normalize();
        unitBall2Velocity.normalize();

        int isLeft1, isLeft2;

        isLeft1 = velocityDirection(unitBall1Velocity, l12);
        isLeft2 = velocityDirection(unitBall2Velocity, l21);

        float alphaV1S = getAlpha(unitBall1Velocity, l12), alphaV2S = getAlpha(unitBall2Velocity, l21);
        Eigen::Matrix2f rotateMatrix1;
        rotateMatrix1 << cos(alphaV1S), isLeft1 * sin(alphaV1S),
                         isLeft1 * -1 * sin(alphaV1S), cos(alphaV1S);
        Eigen::Vector2f newVelocity1 = unitBall1Velocity.transpose() * rotateMatrix1 * (ball1V * sin(alphaV1S));
        
        /* std::cout << "ball1Velocity:\n" << unitBall1Velocity << "\nl12:\n" << l12 << "\nball1Alpha:\t" << alphaV1S << std::endl; */
        /* ball2.changeVelocity(cos(alphaV1S) * ball1.getVelocity().norm() * l12); */
        Eigen::Matrix2f rotateMatrix2;
        rotateMatrix2 << cos(alphaV2S), isLeft2 * sin(alphaV2S),
                        isLeft2 * -1 * sin(alphaV2S), cos(alphaV2S);
        Eigen::Vector2f newVelocity2 = cos(alphaV1S) * ball1.getVelocity().norm() * l12;
        
        /* std::cout << "ball2Velocity:\n" << unitBall2Velocity << "\nl21:\n" << l21 << "\nball2Alpha:\t" << alphaV2S << std::endl; */

        ball2.changeVelocity(newVelocity2, "");
        ball1.changeVelocity(newVelocity1);
        /* ball1.changeVelocity(((1 / ball1Velocity.norm()) * ball1Velocity).transpose() * rotateMatrix * (ball1Velocity.norm() * sin(alphaV1S))); */

    }
}
