#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include "snake.h"
#include "food.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;
    void snakeGrow();
    
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Snake snake_p1;
    food currentFoods;
    int currentSpeed; 
    int foodUpdateSpeed; // 食物刷新速度
    QTimer *gameTimer; // 游戏总计时器，负责刷新页面
    QTimer *foodTimer; // 负责食物的刷新
    void timeTick();
    void drawGrid(QPainter *painter); // 绘制网格
    void drawSnake(QPainter *painter); // 绘制蛇
    void drawFood(QPainter *painter); // 绘制食物
    void drawDieScene(QPainter *painter);
    bool isGameOver(); // 判断游戏是否结束
    int eatFood(); // 判断蛇有没有吃到食物
    void generateFood(); // 与food类连接，产生新的食物
};
#endif // WIDGET_H
