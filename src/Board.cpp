#include "Board.hpp"

//46, 139, 87
#define BOARD_COLOR sf::Color(51, 161, 201)
#define BOARD_OUTLINE_COLOR sf::Color(255, 192, 203)

Board::Board(): _outBoard(sf::Vector2f(760, 360)),
    _blackBall(sf::Color::Black, sf::Vector2f(300.f, 200.f), "Black", "8"),
    _whiteBall(sf::Color::White, sf::Vector2f(400.f, 300.f), "White", "x")
{
    //台球桌面
    _outBoard.setPosition(20.f, 20.f);
    _outBoard.setFillColor(BOARD_COLOR);
    _outBoard.setOutlineThickness(20.f);
    _outBoard.setOutlineColor(BOARD_OUTLINE_COLOR);
    
    //台球六个洞口绘制
    int k=0;
    float x=10.f, y=10.f, step=750.f;
    for (int i=0; i<2; i++)
    {
        for (int j=0; j<2; j++)
        {
            _ballHolesPosList[k].x = x;
            _ballHolesPosList[k].y = y;
            x += step;
            k += 2;
        }
        k -= 3;
        x -= step;
        _ballHolesPosList[k].x = x - step/2;
        _ballHolesPosList[k].y = y - step/60;
        k += 2;
        step *= -1;
        y = 370 - y;
    }
    for (int i=0; i<6; i++)
    {
        sf::CircleShape ballHole;
        ballHole.setPosition(_ballHolesPosList[i].x, _ballHolesPosList[i].y);
        ballHole.setRadius(15);
        ballHole.setPointCount(40);
        ballHole.setFillColor(sf::Color::Black);
        _ballHoles.push_back(ballHole);
    }

    //库边绘制
    _staticCreator.createPoolSides();
  
    //发球线
    _startLine.setFillColor(BOARD_OUTLINE_COLOR);
    _startLine.setPosition(sf::Vector2f(165.f, 25.f));
    _startLine.setSize(sf::Vector2f(2.f, 360.f));

    //发球线中点
    _centerPoint.setFillColor(BOARD_OUTLINE_COLOR);
    _centerPoint.setPosition(161.5f, 197.5f);
    _centerPoint.setRadius(5);

    //摆球点
    _initPoint.setFillColor(BOARD_OUTLINE_COLOR);
    _initPoint.setPosition(780.f - 200.f, 197.5f);
    _initPoint.setRadius(5);
    
    _blackBall.changeVelocity(Eigen::Vector2f(0.1f, 0.09f));

}

Ball& Board::getBlackBall()
{
    return _blackBall;
}

void Board::update(sf::Time deltaTime)
{

    std::vector<PoolSide> poolSides = _staticCreator.getPoolSides();
    for (auto iter = poolSides.begin(); iter!=poolSides.end(); iter++)
    {

        if (_blackBall.getVelocity()(0, 0) != 0.f && _blackBall.getVelocity()(1, 0) != 0.f)
            _myPhyics.collision(_blackBall, *iter);
        if (_whiteBall.getVelocity()(0, 0) != 0.f && _whiteBall.getVelocity()(1, 0) != 0.f )
            _myPhyics.collision(_whiteBall, *iter);
    }
    if (_blackBall.getVelocity()(0, 0) != 0.f && _blackBall.getVelocity()(1, 0) != 0.f)
    {
        _myPhyics.collision(_blackBall, _whiteBall);
        /* _blackBall.update(deltaTime); */
        /* _whiteBall.update(deltaTime); */
        /* return; */
    }
    if (_whiteBall.getVelocity()(0, 0) != 0.f && _whiteBall.getVelocity()(1, 0) != 0.f)
    /* { */
        _myPhyics.collision(_whiteBall, _blackBall);
        _blackBall.update(deltaTime);
        _whiteBall.update(deltaTime);
    /* } */
    /* std::cout << "black:\t" << _blackBall.getVelocity() << std::endl << "white:\t" << _whiteBall.getVelocity() << std::endl; */
}


void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_outBoard, states);
    for (int i=0; i<6; i++)
    {
        /* target.draw(_poolSides.at(i), states); */
        target.draw(_ballHoles[i], states);
    }
    target.draw(_staticCreator, states);
    target.draw(_startLine, states);
    target.draw(_centerPoint, states);
    target.draw(_initPoint, states);
    target.draw(_blackBall, states);
    target.draw(_whiteBall, states);
}
