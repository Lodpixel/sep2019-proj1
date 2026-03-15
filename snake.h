#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <deque>
class Snake
{
public:
    enum Direction
    {
        Left,
        Up,
        Down,
        Right
    };
    Snake();
    std::deque<QPoint> body;
    int getlength();
    void move();
    void changeDir(Direction dir);

private:
    Direction currentDir;
    int length;
};

#endif // SNAKE_H
