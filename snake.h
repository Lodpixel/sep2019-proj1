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
    enum SnakeState
    {
        Normal,
        Die
    };
    Snake();
    std::deque<QPoint> body;
    int getlength();
    SnakeState currentState;
    void move();
    void changeDir(Direction dir);

private:
    Direction currentDir;
    int length;
    bool outOfRange(const QPoint &point);
    bool hitItself(const QPoint &point);
};

#endif // SNAKE_H
