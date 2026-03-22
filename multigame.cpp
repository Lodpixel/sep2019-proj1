#include "multigame.h"
#include "config.h"
MultiGame::MultiGame(QWidget *parent) : GameCore{parent}
{
    initChaosTimer();
    QPoint start = QPoint(GameConfig::nodeSize * (GameConfig::columns - 1), GameConfig::nodeSize * (GameConfig::rows / 2));
    snake_p2 = Snake(start, Snake::Left, 5, 2);
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

void MultiGame::drawScore(QPainter *painter)
{
    GameCore::drawScore(painter);
    painter->setPen(Qt::white);
    painter->setFont(QFont("Microsoft YaHei", 12));
    painter->drawText(10, 500, QString("P2分数: %1").arg(snake_p2.score));
}

void MultiGame::restart()
{
    QPoint start = QPoint(GameConfig::nodeSize * (GameConfig::columns - 1), GameConfig::nodeSize * (GameConfig::rows / 2));
    snake_p2 = Snake(start, Snake::Left, 5, 2);
    GameCore::restart();
}
    

void MultiGame::timeTick()
{
    snake_p1.move();
    snake_p2.move();
    switch (eatFood(snake_p1))
    {
    case singleFood::normal:
        eatNormal(snake_p1);
        break;
    case singleFood::chaos:
        eatChaos_p1(snake_p1);
        break;
    }
    switch (eatFood(snake_p2))
    {
    case singleFood::normal:
        eatNormal(snake_p2);
        break;
    case singleFood::chaos:
        eatChaos_p2(snake_p2);
        break;
    }
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
    if (snake_p1.score >= 2000)
    {
        winner = 1;
        endGame();
    }
    if (snake_p2.score >= 2000)
    {
        winner = 2;
        endGame();
    }
    this->update();
}

void MultiGame::keyPressEvent(QKeyEvent *event)
{qDebug() << "key pressed!";
    int key = event->key();
    
    GameCore::keyPressEvent(event);
    bool p2Chaos = (snake_p2.currentState == Snake::Chaos);
    Snake::Direction Dir;
    switch (key)
    {
    case Qt::Key_Up:
        Dir = p2Chaos ? Snake::Down : Snake::Up;
        snake_p2.changeDir(Dir);
        break;
    case Qt::Key_Left:
        Dir = p2Chaos ? Snake::Right : Snake::Left;
        snake_p2.changeDir(Dir);
        break;
    case Qt::Key_Down:
        Dir = p2Chaos ? Snake::Up : Snake::Down;
        snake_p2.changeDir(Dir);
        break;
    case Qt::Key_Right:
        Dir = p2Chaos ? Snake::Left : Snake::Right;
        snake_p2.changeDir(Dir);
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void MultiGame::initChaosTimer()
{
    chaosTimer_p1 = new QTimer(this);
    connect(chaosTimer_p1, &QTimer::timeout, [this]() {
        snake_p1.currentState = Snake::Normal;
        chaosTimer_p1->stop();
    });

    chaosTimer_p2 = new QTimer(this);
    connect(chaosTimer_p2, &QTimer::timeout, [this]() {
        snake_p2.currentState = Snake::Normal;
        chaosTimer_p2->stop();
    });
}

void MultiGame::eatChaos_p1(Snake &snake)
{
    snake.currentState = Snake::Chaos;
    chaosTimer_p1->start(chaosTime);
}

void MultiGame::eatChaos_p2(Snake &snake)
{
    snake.currentState = Snake::Chaos;
    chaosTimer_p2->start(chaosTime);
}