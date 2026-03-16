#include "widget.h"
#include "snake.h"
#include "config.h"
#include "food.h"
#include <QPainter>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    currentSpeed = 400;
    setFixedSize(800, 600);
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Widget::timeTick);
    gameTimer->start(currentSpeed);
}

Widget::~Widget() = default;

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(40, 44, 52));
    painter.drawRect(this->rect());
    painter.setBrush(Qt::NoBrush);
    if (isGameOver())
    {
        drawDieScene(&painter);
    }
    painter.setRenderHint(QPainter::Antialiasing);
    drawGrid(&painter);
    drawSnake(&painter);
    drawFood(&painter);
}
// 绘制网格
void Widget::drawGrid(QPainter *painter)
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
// 绘制蛇
void Widget::drawSnake(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::green);
    for (const auto &pos : snake_p1.body)
    {
        painter->drawRect(pos.x() + 1, pos.y() + 1, GameConfig::nodeSize - 2, GameConfig::nodeSize - 2); // 留出网格的空间，体现像素感
    }
}

void Widget::drawFood(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::blue);
    for (const auto &pos : currentFoods.foods)
    {
        painter->drawRect(pos.x() + 1, pos.y() + 1, GameConfig::nodeSize - 2, GameConfig::nodeSize - 2);
    }
}

void Widget::drawDieScene(QPainter *painter)
{
}

void Widget::timeTick()
{
    QPoint Point = snake_p1.move();
    int index = eatFood();
    if (index != -1) // 如果吃到食物
    {
        currentFoods.foods.erase(currentFoods.foods.begin() + index);
        snake_p1.snakeGrow();
    }
    if (snake_p1.isDead())
    {
        qDebug() << "Die!! 死亡坐标:" << Point;
        snake_p1.currentState = Snake::Die;
    }
    this->update();
}

void Widget::keyPressEvent(QKeyEvent *event)
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

bool Widget::isGameOver()
{
    if (snake_p1.currentState == Snake::Die)
    {
        gameTimer->stop();
        return true;
    }
    return false;
}

// 返回food的索引，如果没找到，返回-1
int Widget::eatFood()
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