#include "multigame.h"
#include "config.h"
MultiGame::MultiGame(QWidget *parent) : GameCore{parent}
{
    QPoint start = QPoint(GameConfig::nodeSize * (GameConfig::columns - 1), GameConfig::nodeSize * (GameConfig::rows / 2));
    snake_p2 = Snake(start, Snake::Left, 5);
}

void MultiGame::drawSnake(QPainter *painter)
{
    GameCore::drawSnake(painter);
    painter->setBrush(Qt::red);
    for (const auto &pos : snake_p2.body)
    {
        painter->drawRect(pos.x() + 1, pos.y() + 1, GameConfig::nodeSize - 2, GameConfig::nodeSize - 2); // 留出网格的空间，体现像素感
    }
}

void MultiGame::restart()
{
    QPoint start = QPoint(GameConfig::nodeSize * (GameConfig::columns - 1), GameConfig::nodeSize * (GameConfig::rows / 2));
    snake_p2 = Snake(start, Snake::Left, 5);
    GameCore::restart();
}
    

void MultiGame::timeTick()
{
    snake_p1.move();
    snake_p2.move();
    eatFood(snake_p1);
    eatFood(snake_p2);
    checkFood();
    if (snake_p1.isDead() || snake_p1.hitOtherSnake(snake_p2))
    {
        afterSnakeDie(snake_p1);
        if (snake_p2.isDead() || snake_p2.hitOtherSnake(snake_p1))
        {
            winner = 0;
            afterSnakeDie(snake_p2);
            endGame();
            this->update();
            return;
        }
        winner = 2;
        endGame();
        this->update();
        return;
    }
    if (snake_p2.isDead() || snake_p2.hitOtherSnake(snake_p1))
    {
        qDebug() << "2die!";
        afterSnakeDie(snake_p2);
        winner = 1;
        endGame();
    }
    this->update();
}

void MultiGame::keyPressEvent(QKeyEvent *event)
{qDebug() << "key pressed!";
    int key = event->key();
    
    GameCore::keyPressEvent(event);
    
    switch (key)
    {
    case Qt::Key_Up:
        snake_p2.changeDir(Snake::Up);
        break;
    case Qt::Key_Left:
        snake_p2.changeDir(Snake::Left);
        break;
    case Qt::Key_Down:
        snake_p2.changeDir(Snake::Down);
        break;
    case Qt::Key_Right:
        snake_p2.changeDir(Snake::Right);
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}