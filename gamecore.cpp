#include "gamecore.h"
#include "config.h"

GameCore::GameCore(QWidget *parent) : QWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus);
    gameTimer = new QTimer(this);
    foodTimer = new QTimer(this);
    connSig();
}

GameCore::~GameCore() = default;

void GameCore::restart()
{
    currentSpeed = 400;
    speedUpRate = 0.95;
    foodUpdateSpeed = 5000;
    snake_p1 = Snake(QPoint(0, GameConfig::nodeSize * (GameConfig::rows / 2)), Snake::Right, 5, 1);
    currentFoods.reset();
    gameTimer->start(currentSpeed);
    foodTimer->start(foodUpdateSpeed);
}

void GameCore::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(40, 44, 52));
    painter.drawRect(this->rect());
    painter.setBrush(Qt::NoBrush);
    painter.setRenderHint(QPainter::Antialiasing);
    drawGrid(&painter);
    drawSnake(&painter);
    drawFood(&painter);
    drawScore(&painter);
}

void GameCore::drawGrid(QPainter *painter)
{
    painter->setPen(QColor(255, 255, 255, 30));
    for (int i = 1; i < GameConfig::columns; ++i)
    {
        painter->drawLine(i * GameConfig::nodeSize, 0, i * GameConfig::nodeSize, GameConfig::rows * GameConfig::nodeSize);
    }
    for (int j = 1; j < GameConfig::rows; ++j)
    {
        painter->drawLine(0, j * GameConfig::nodeSize, GameConfig::columns * GameConfig::nodeSize, j * GameConfig::nodeSize);
    }
}

void GameCore::drawSnake(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::green);
    for (const auto &pos : snake_p1.body)
    {
        painter->drawRect(pos.x() + 1, pos.y() + 1, GameConfig::nodeSize - 2, GameConfig::nodeSize - 2); // 留出网格的空间，体现像素感
    }
}

void GameCore::drawFood(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    for (const auto &curFood : currentFoods.foods)
    {
        switch (curFood.type)
        {
        case singleFood::normal:
            painter->setBrush(Qt::blue);
            break;
        case singleFood::chaos:
            painter->setBrush(QColor(128, 0, 128));
            break;
        }
        QPoint pos = curFood.point;
        painter->drawRect(pos.x() + 1, pos.y() + 1, GameConfig::nodeSize - 2, GameConfig::nodeSize - 2);
    }
}

void GameCore::drawScore(QPainter *painter)
{
    painter->setPen(Qt::white);
    painter->setFont(QFont("Microsoft YaHei", 12));
    painter->drawText(10, 20, QString("P1分数: %1").arg(snake_p1.score));
}

void GameCore::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    Snake::Direction Dir;
    bool p1Chaos = (snake_p1.currentState == Snake::Chaos);
    qDebug() << p1Chaos << "IN chaos!";
    switch (key)
    {
    case Qt::Key_W:
        Dir = p1Chaos ? Snake::Down : Snake::Up;
        snake_p1.changeDir(Dir);
        break;
    case Qt::Key_A:
        Dir = p1Chaos ? Snake::Right : Snake::Left;
        snake_p1.changeDir(Dir);
        break;
    case Qt::Key_S:
        Dir = p1Chaos ? Snake::Up : Snake::Down;
        snake_p1.changeDir(Dir);
        break;
    case Qt::Key_D:
        Dir = p1Chaos ? Snake::Left : Snake::Right;
        snake_p1.changeDir(Dir);
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

singleFood::foodType GameCore::eatFood(Snake &snake)
{
    for (int i = 0; i < currentFoods.foods.size(); ++i)
    {
        if (snake.head == currentFoods.foods[i].point)
        {
            singleFood::foodType type = currentFoods.foods[i].type;
            currentFoods.foods.erase(currentFoods.foods.begin() + i);
            return type;
        }
    }
    return singleFood::none;
}

void GameCore::eatNormal(Snake &snake)
{
    snake.snakeGrow();
    snake.addScore(50);
    speedUp();
}

void GameCore::generateFood()
{
    if (currentFoods.foods.size() < food::maxFood)
    {
        currentFoods.generateFood();
    }
}

void GameCore::connSig()
{
    connect(gameTimer, &QTimer::timeout, this, &GameCore::timeTick);
    connect(foodTimer, &QTimer::timeout, this, &GameCore::generateFood);
}

void GameCore::afterSnakeDie(Snake &snake)
{
    if (!snake.body.empty())
    {
        snake.body.pop_front();
        snake.body.push_back(snake.lastPoppedTail);
        snake.head = snake.body.front();
    }
    snake.currentState = Snake::Die;
}

void GameCore::checkFood()
{
    if (currentFoods.foods.size() < food::minFood)
    {
        currentFoods.generateFood();
        foodTimer->start(foodUpdateSpeed);
    }
}

void GameCore::endGame()
{
    gameTimer->stop();
    foodTimer->stop();
    emit gameOverSignal();
    this->update();
}

void GameCore::speedUp()
{
    if (currentSpeed > GameConfig::maxSpeed)
    {
        currentSpeed *= speedUpRate;
        gameTimer->start(currentSpeed);
    }
}