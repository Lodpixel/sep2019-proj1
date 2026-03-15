#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "snake.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;
    
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Snake snake_p1;
    int currentSpeed;
    QTimer *gameTimer;
    void timeTick();
    void drawGrid(QPainter *painter); // 绘制网格
    void drawSnake(QPainter *painter); // 绘制蛇
    void drawFood(QPainter *painter); // 绘制食物
};
#endif // WIDGET_H
