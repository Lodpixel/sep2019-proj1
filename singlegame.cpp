#include "singlegame.h"
#include "config.h"

SingleGame::SingleGame(QWidget *parent) : GameCore(parent)
{
    chaosTimer_p1 = new QTimer(this);
    connect(chaosTimer_p1, &QTimer::timeout, [this]() {
        snake_p1.currentState = Snake::Normal;
        chaosTimer_p1->stop();
    });
}

SingleGame::~SingleGame() = default;

void SingleGame::timeTick()
{
    snake_p1.move();
    switch (eatFood(snake_p1))
    {
    case singleFood::normal:
        eatNormal(snake_p1);
        break;
    case singleFood::chaos:
        eatChaos(snake_p1);
        break;
    }
    checkFood();
    if (snake_p1.isDead())
    {
        afterSnakeDie(snake_p1);
        endGame();
    }
    this->update();
}

void SingleGame::eatChaos(Snake &snake)
{
    snake.currentState = Snake::Chaos;
    chaosTimer_p1->start(chaosTime);
}