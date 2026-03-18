#include "singlegame.h"
#include "config.h"

SingleGame::SingleGame(QWidget *parent) : GameCore(parent)
{
}

SingleGame::~SingleGame() = default;

void SingleGame::timeTick()
{
    snake_p1.move();
    eatFood(snake_p1);
    checkFood();
    if (snake_p1.isDead())
    {
        afterSnakeDie(snake_p1);
        endGame();
    }
    this->update();
}
