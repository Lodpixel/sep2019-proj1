#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include "snake.h"
#include "food.h"

class SingleGame : public QWidget
{
    Q_OBJECT

public:
    explicit SingleGame(QWidget *parent = nullptr);
    ~SingleGame() override;
    void snakeGrow();
    void restart();
    
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void gameOverSignal();

private:
    Snake snake_p1;
    food currentFoods;
    int currentSpeed;
    int foodUpdateSpeed; // 食物刷新速度
    float speedUpRate; // 加速比例
    QTimer *gameTimer; // 游戏总计时器，负责刷新页面
    QTimer *foodTimer; // 负责食物的刷新
    QPushButton *restartBtn = nullptr;
    void timeTick();
    void drawGrid(QPainter *painter); // 绘制网格
    void drawSnake(QPainter *painter); // 绘制蛇
    void drawFood(QPainter *painter); // 绘制食物
    bool isGameOver(); // 判断游戏是否结束
    int eatFood(); // 判断蛇有没有吃到食物
    void generateFood(); // 与food类连接，产生新的食物
    
};

#endif // SINGLEGAME_H