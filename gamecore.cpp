#include "gamecore.h"
#include "config.h"

GameCore::GameCore(QWidget *parent) : QWidget{parent}
{
    gameTimer = new QTimer(this);
    foodTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameCore::timeTick);
    connect(foodTimer, &QTimer::timeout, this, &GameCore::generateFood);
}

GameCore::~GameCore() = default;

void GameCore::restart()
{
    currentSpeed = 400;
    speedUpRate = 0.95;
    foodUpdateSpeed = 5000;
    snake_p1 = Snake();
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
    painter->setBrush(Qt::blue);
    for (const auto &pos : currentFoods.foods)
    {
        painter->drawRect(pos.x() + 1, pos.y() + 1, GameConfig::nodeSize - 2, GameConfig::nodeSize - 2);
    }
}

void GameCore::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    switch (key)
    {
    case Qt::Key_W:
        snake_p1.changeDir(Snake::Up);
        break;
    case Qt::Key_A:
        snake_p1.changeDir(Snake::Left);
        break;
    case Qt::Key_S:
        snake_p1.changeDir(Snake::Down);
        break;
    case Qt::Key_D:
        snake_p1.changeDir(Snake::Right);
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void GameCore::eatFood(Snake &snake)
{
    for (int i = 0; i < currentFoods.foods.size(); ++i)
    {
        if (snake.head == currentFoods.foods[i])
        {
            currentFoods.foods.erase(currentFoods.foods.begin() + i);
            snake.snakeGrow();
            speedUp();
        }
    }
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
        snake.body.push_back(snake_p1.lastPoppedTail);
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