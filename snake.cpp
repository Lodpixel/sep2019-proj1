#include "snake.h"
#include "config.h"
#include <deque>

Snake::Snake()
{
    length = 5;
    QPoint Point(GameConfig::nodeSize, GameConfig::rows * GameConfig::nodeSize / 2);
    int count = length;
    while (count--)
    {
        body.push_front(Point);
        Point.rx() += GameConfig::nodeSize;
    }

    currentDir = Right;
}

int Snake::getlength() { return length; }

void Snake::move()
{
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
    body.pop_back();
}

void Snake::changeDir(Direction dir)
{
    if (dir + currentDir != 3) // 防止方向相反（方法比较神秘，但节省大量代码）
    {
        currentDir = dir;
    }
}