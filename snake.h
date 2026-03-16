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
    QPoint head;
    QPoint lastPoppedTail;
    SnakeState currentState;
    std::deque<QPoint> body;
    Snake();
    int getlength();
    QPoint move(); // 返回头部的位置
    void changeDir(Direction dir);
    void snakeGrow();
    bool isDead();

private:
    Direction currentDir;
    bool canTurnThisTick;
    int length;
    bool outOfRange();
    bool hitItself();
};

#endif // SNAKE_H
