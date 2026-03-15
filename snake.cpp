#include "snake.h"
#include <deque>

Snake::Snake()
{
    length = 5;
    QPoint Point(Widget::nodeSize, Widget::rows * Widget::nodeSize / 2);
    int count = length;
    while (count--)
    {
        body.push_front(Point);
        Point.rx() += Widget::nodeSize;
    }

    currentDir = Right;
}

int Snake::getlength() { return length; }

int Snake::move()
{
    QPoint Point = body.front();
    switch (currentDir)
    {
    case Up:
        Point.ry() += widget.nodeSize;
        break;
    case Down:
        Point.ry() -= widget.nodeSize;
        break;
    case Left:
        Point.rx() -= widget.nodeSize;
        break;
    case Right:
        Point.rx() += widget.nodeSize;
        break;
    }
    body.push_front(Point);
    body.pop_back();
}