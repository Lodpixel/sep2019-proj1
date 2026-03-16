#include "snake.h"
#include "config.h"
#include <deque>
#include <QDebug>
// 蛇中每个体节的坐标是所在图格的左上角坐标
Snake::Snake()
{
    length = 5;
    QPoint Point(0, GameConfig::rows * GameConfig::nodeSize / 2);
    int count = length;
    while (count--)
    {
        body.push_front(Point);
        Point.rx() += GameConfig::nodeSize;
    }
    currentState = Normal;
    currentDir = Right;
    canTurnThisTick = true;
}

int Snake::getlength() { return length; }

QPoint Snake::move()
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
    canTurnThisTick = true;
    return Point;
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