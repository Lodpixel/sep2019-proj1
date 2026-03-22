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
        Chaos,
        Die
    };
    QPoint head;
    QPoint lastPoppedTail;
    SnakeState currentState;
    std::deque<QPoint> body;
    int id;
    int score;
    Snake(QPoint startPos, Direction dir, int len, int id);
    Snake();
    int getlength();
    void move(); // 返回头部的位置
    void changeDir(Direction dir);
    void snakeGrow();
    void addScore(int delta);
    bool isDead();
    bool hitOtherSnake(const Snake& snake);

private:
    Direction currentDir;
    bool canTurnThisTick;
    int length;
    bool outOfRange();
    bool hitItself();
};

#endif // SNAKE_H
