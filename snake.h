#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <deque>
class Snake
{
public:
    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };
    Snake();
    int getlength();
    void move();
    std::deque<QPoint> body;

private:
    Direction currentDir;
    int length;
};

#endif // SNAKE_H
