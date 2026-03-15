#include "widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 600);
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

void Widget::drawGrid(QPainter *painter)
{
    for (int i = 1; i < columns; ++i)
    {
        painter->drawLine(i * nodeSize, 0, i * nodeSize, rows * nodeSize);
    }
    for (int j = 1; j < rows; ++j)
    {
        painter->drawLine(0, j * nodeSize, columns * nodeSize, j * nodeSize);
    }
}

void Widget::drawSnake(QPainter *painter)
{

}

void Widget::drawFood(QPainter *painter)
{

}