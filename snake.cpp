#include "snake.h"
#include "config.h"
#include <deque>
#include <QDebug>
// 蛇中每个体节的坐标是所在图格的左上角坐标
Snake::Snake(QPoint Point, Direction dir, int len, int id)
{
    int count = len;
    while (count--)
    {
        body.push_front(Point);
        switch(dir)
        {
        case Right:
            currentDir = Right;
            Point.rx() += GameConfig::nodeSize;
            break;
        case Left:
            currentDir = Left;
            Point.rx() -= GameConfig::nodeSize;
            break;
        case Up:
            currentDir = Up;
            Point.ry() -= GameConfig::nodeSize;
            break;
        case Down:
            currentDir = Down;
            Point.ry() += GameConfig::nodeSize;
        }
    }
    currentState = Normal;
    canTurnThisTick = true;
    this->id = id;
    score = 0;
    head = body.front();
}

Snake::Snake() {}

int Snake::getlength() { return length; }

void Snake::move()
{
    // 移动逻辑
    QPoint Point = body.front();
    switch (currentDir)
    {
    case Up:
        Point.ry() -= GameConfig::nodeSize;
        break;
    case Down:
        Point.ry() += GameConfig::nodeSize;
        break;
    case Left:
        Point.rx() -= GameConfig::nodeSize;
        break;
    case Right:
        Point.rx() += GameConfig::nodeSize;
        break;
    }
    body.push_front(Point);
    head = Point;
    if (!body.empty())
    {
        lastPoppedTail = body.back();
        body.pop_back();
    }
    addScore(1);
    canTurnThisTick = true;
}

void Snake::changeDir(Direction dir)
{
    if (!canTurnThisTick)
    {
        return;
    }

    if (dir + currentDir != 3 && dir != currentDir) // 防止方向相反，并且每tick只允许一次有效转向
    {
        currentDir = dir;
        canTurnThisTick = false;
    }
}
// 判断是否超界
bool Snake::outOfRange()
{
    if (head.x() >= GameConfig::columns * GameConfig::nodeSize || head.x() < 0)
    {
        return true;
    }
    if (head.y() >= GameConfig::rows * GameConfig::nodeSize || head.y() < 0)
    {
        return true;
    }
    return false;
}
// 判断是否撞自己
bool Snake::hitItself()
{
    if (body.size() <= 1)
    {
        return false;
    }

    for (size_t i = 1; i < body.size(); ++i)
    {
        if (body[i] == head)
            return true;
    }
    return false;
}

void Snake::snakeGrow()
{
    body.push_back(lastPoppedTail);
    return;
}

bool Snake::isDead()
{
    return outOfRange() || hitItself();
}

bool Snake::hitOtherSnake(const Snake& snake)
{
    for (size_t i = 0; i < snake.body.size(); ++i)
    {
        if (snake.body[i] == head)
            return true;
    }
    return false;
}

void Snake::addScore(int delta)
{
    int isChaos = (currentState == Chaos) ? 1 : 0;
    score += delta * (1 + isChaos);
}