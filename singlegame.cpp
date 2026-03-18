#include "singlegame.h"
#include "snake.h"
#include "config.h"
#include "food.h"
#include <QPainter>
#include <QLabel>
#include <QPushButton>

SingleGame::SingleGame(QWidget *parent) : QWidget(parent)
{
    gameTimer = new QTimer(this);
    foodTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &SingleGame::timeTick);
    connect(foodTimer, &QTimer::timeout, this, &SingleGame::generateFood);
    restart(); // 调用启动函数
}

SingleGame::~SingleGame() = default;

void SingleGame::restart()
{
    currentSpeed = 400;
    speedUpRate = 0.95;
    foodUpdateSpeed = 5000;
    snake_p1 = Snake();
    currentFoods.reset();
    gameTimer->start(currentSpeed);
    foodTimer->start(foodUpdateSpeed);
}

void SingleGame::paintEvent(QPaintEvent *event)
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

void SingleGame::drawGrid(QPainter *painter)
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

void SingleGame::drawSnake(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::green);
    for (const auto &pos : snake_p1.body)
    {
        painter->drawRect(pos.x() + 1, pos.y() + 1, GameConfig::nodeSize - 2, GameConfig::nodeSize - 2); // 留出网格的空间，体现像素感
    }
}

void SingleGame::drawFood(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::blue);
    for (const auto &pos : currentFoods.foods)
    {
        painter->drawRect(pos.x() + 1, pos.y() + 1, GameConfig::nodeSize - 2, GameConfig::nodeSize - 2);
    }
}

void SingleGame::timeTick()
{
    snake_p1.move();
    int index = eatFood();
    if (index != -1) // 如果吃到食物
    {
        currentFoods.foods.erase(currentFoods.foods.begin() + index);
        snake_p1.snakeGrow();
        if (currentSpeed > 80)
        {
            currentSpeed *= speedUpRate;
            gameTimer->start(currentSpeed);
        }
    }
    if (currentFoods.foods.size() < food::minFood)
    {
        currentFoods.generateFood();
        foodTimer->start(foodUpdateSpeed);
    }
    if (snake_p1.isDead())
    {
        if (!snake_p1.body.empty())
        {
            snake_p1.body.pop_front();
            snake_p1.body.push_back(snake_p1.lastPoppedTail);
            snake_p1.head = snake_p1.body.front();
        }
        snake_p1.currentState = Snake::Die;
        gameTimer->stop();
        foodTimer->stop();
        emit gameOverSignal();
        this->update();
        return;
    }
    this->update();
}

void SingleGame::keyPressEvent(QKeyEvent *event)
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

bool SingleGame::isGameOver()
{
    if (snake_p1.currentState == Snake::Die)
    {
        gameTimer->stop();
        return true;
    }
    return false;
}

int SingleGame::eatFood()
{
    for (int i = 0; i < currentFoods.foods.size(); ++i)
    {
        if (snake_p1.head == currentFoods.foods[i])
        {
            return i;
        }
    }
    return -1;
}

void SingleGame::generateFood()
{
    if (currentFoods.foods.size() < food::maxFood)
    {
        currentFoods.generateFood();
    }
}
