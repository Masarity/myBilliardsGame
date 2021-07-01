#include "Physics.hpp"
#include <math.h>

Physics::Physics(){}

Physics::~Physics(){}

float getAlpha(Eigen::Vector2f a, Eigen::Vector2f b)
{
    if (a.norm() * b.norm() == 0.f)
        return 0.f;
    float ret = acos(a.dot(b.transpose()) / (a.norm() * b.norm()));
    std::cout << "a.dot(b.transpose()):\t" << a.dot(b.transpose())
        << "\na.norm() * b.norm():\t" << a.norm() * b.norm() << std::endl;
    return !isnan(ret) ? ret : 0.f;
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
    /* sf::FloatRect ball1Box = ball1.getBall().getGlobalBounds(); */
    /* sf::FloatRect ball2Box = ball2.getBall().getGlobalBounds(); */
    /* if (ball1Box.intersects(ball2Box)) */
    /* { */
        Eigen::Vector2f v12 = ball2.getPos() - ball1.getPos();
        Eigen::Vector2f l12 = (1 / v12.norm()) * v12;
        Eigen::Vector2f v21 = ball1.getPos() - ball2.getPos();
        Eigen::Vector2f l21 = (1 / v21.norm()) * v21;

        std::cout << v12 << fabs(v12.norm() - 9) << std::endl;
    if (fabs(v12.norm() - 9) < 20.f)
    {
        Eigen::Vector2f ball1Velocity = ball1.getVelocity();
        Eigen::Vector2f ball2Velocity = ball2.getVelocity();

        int isLeft, isRight;

        isLeft = velocityDirection((1 / (ball1Velocity.norm() ? ball1Velocity.norm() : 1)) * ball1Velocity, l12);
        isRight = -1 * velocityDirection((1 / (ball2Velocity.norm() ? ball2Velocity.norm() : 1)) * ball2Velocity, l21);

        float alphaV1S = getAlpha(ball1Velocity, l12), alphaV2S = getAlpha(ball2Velocity, l21);
        Eigen::Matrix2f rotateMatrix1;
        rotateMatrix1 << cos(alphaV1S), isLeft * sin(alphaV1S),
                         isLeft * -1 * sin(alphaV1S), cos(alphaV1S);
        Eigen::Vector2f newVelocity11 = (cos(alphaV2S) * ball2.getVelocity().norm() * l21);
        Eigen::Vector2f newVelocity12 = ((1 / (ball1Velocity.norm() ? ball1Velocity.norm() : 1)) * ball1Velocity).transpose() * rotateMatrix1 * (ball1Velocity.norm() * sin(alphaV1S));
        
        std::cout << "ball1Velocity:\n" << ball1Velocity << "\nv12:\n" << v12 << "\nball1Alpha:\t" << alphaV1S << std::endl;
        std::cout << "newVelocity11:\n" << newVelocity11 << "\nnewVelocity12:\n" << newVelocity12 << std::endl;
        /* ball2.changeVelocity(cos(alphaV1S) * ball1.getVelocity().norm() * l12); */
        Eigen::Matrix2f rotateMatrix2;
        rotateMatrix2 << cos(alphaV2S), isRight * sin(alphaV2S),
                        isRight * -1 * sin(alphaV2S), cos(alphaV2S);
        Eigen::Vector2f newVelocity21 = cos(alphaV1S) * ball1.getVelocity().norm() * l12;
        Eigen::Vector2f newVelocity22 = ((1 / (ball2Velocity.norm() ? ball2Velocity.norm() : 1)) * ball2Velocity).transpose() * rotateMatrix2 * (ball2Velocity.norm() * sin(alphaV2S));         
        
        std::cout << "ball2Velocity:\n" << ball2Velocity << "\nv21:\n" << v21 << "\nball2Alpha:\t" << alphaV2S << std::endl;
        std::cout << "newVelocity21:\n" << newVelocity21 << "\nnewVelocity22:\n" << newVelocity22 << std::endl;

        ball2.changeVelocity(newVelocity21 + newVelocity22);
        ball1.changeVelocity(newVelocity11 + newVelocity12);
        /* ball1.changeVelocity(((1 / ball1Velocity.norm()) * ball1Velocity).transpose() * rotateMatrix * (ball1Velocity.norm() * sin(alphaV1S))); */

    }
}
