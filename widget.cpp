#include "widget.h"
#include "snake.h"
#include "config.h"
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
    painter.setPen(QColor(255, 255, 255, 30));

    painter.setRenderHint(QPainter::Antialiasing);
    drawGrid(&painter);
    drawSnake(&painter);
    drawFood(&painter);
}
// 绘制网格
void Widget::drawGrid(QPainter *painter)
{
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
        painter->drawRect(pos.x() - GameConfig::nodeSize + 1, pos.y() + 1, GameConfig::nodeSize - 2, GameConfig::nodeSize - 2); // 留出网格的空间，体现像素感
    }
}

void Widget::drawFood(QPainter *painter)
{

}

void Widget::timeTick()
{
    snake_p1.move();
    this->update();
}