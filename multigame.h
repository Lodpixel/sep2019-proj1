#ifndef MULTIGAME_H
#define MULTIGAME_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include "snake.h"
#include "food.h"


class MultiGame : public QWidget
{
    Q_OBJECT

public:
    explicit MultiGame(QWidget *parent = nullptr);
    
protected:

signals:

private:
    Snake snake_p1;
    Snake snake_p2;
    food currentFoods;
    int currentSpeed;
    int foodUpdateSpeed; // 食物刷新速度
    float speedUpRate; // 加速比例
    QTimer *gameTimer; // 游戏总计时器，负责刷新页面
    QTimer *foodTimer; // 负责食物的刷新
    QPushButton *restartBtn = nullptr;
};

#endif // MULTIGAME_H
