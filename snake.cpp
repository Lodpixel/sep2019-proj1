#include "snake.h"
#include "config.h"
#include <deque>
#include <QDebug>
// 蛇中每个体节的坐标是所在图格的右上角坐标
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
    currentState = Normal;
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
    if (outOfRange(Point) || hitItself(Point))
    {
        qDebug() << "Die!! 死亡坐标:" << Point;
        currentState = Die;
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
// 判断是否超界
bool Snake::outOfRange(const QPoint &point)
{
   if (point.x() > GameConfig::columns * GameConfig::nodeSize || point.x() <= 0)
   {
        return true;
   } 
   if (point.y() >= GameConfig::rows * GameConfig::nodeSize || point.y() < 0)
   {
        return true;
   }
   return false;
}
// 判断是否撞自己
bool Snake::hitItself(const QPoint &point)
{
    for (auto const &curPoint : body)
    {
        if (curPoint != body.back() && curPoint == point)
            return true;
    }
    return false;
}