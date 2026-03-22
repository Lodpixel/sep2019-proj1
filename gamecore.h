#ifndef GAMECORE_H
#define GAMECORE_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QPoint>
#include <QColor>
#include <QDebug>
#include "snake.h"
#include "food.h"
#include "singlefood.h"

class GameCore : public QWidget
{
    Q_OBJECT
public:
    explicit GameCore(QWidget *parent = nullptr);
    ~GameCore() override;
    virtual void restart();

protected:
    Snake snake_p1;
    
    void paintEvent(QPaintEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void timeTick() = 0;
    void drawGrid(QPainter *painter); // 绘制网格
    virtual void drawSnake(QPainter *painter); // 绘制蛇
    void drawFood(QPainter *painter); // 绘制食物
    virtual void drawScore(QPainter *painter); // 绘制分数
    singleFood::foodType eatFood(Snake &snake); // 判断蛇有没有吃到食物
    void generateFood(); // 与food类连接，产生新的食物
    void checkFood(); // 检查 food 是否低于阈值，如果低于，则生成
    void connSig();
    void afterSnakeDie(Snake& snake);
    void endGame();
    void eatNormal(Snake &snake);
    int chaosTime = 10000; // 混乱状态持续时间

signals:
    void gameOverSignal();

private:
    int currentSpeed;
    int foodUpdateSpeed; // 食物刷新速度
    float speedUpRate; // 加速比例
    food currentFoods;
    QTimer *gameTimer; // 游戏总计时器，负责刷新页面
    QTimer *foodTimer; // 负责食物的刷新
    void speedUp();
};

#endif // GAMECORE_H
