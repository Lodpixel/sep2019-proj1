#ifndef MULTIGAME_H
#define MULTIGAME_H

#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QDebug>
#include "snake.h"
#include "gamecore.h"
#include "food.h"


class MultiGame : public GameCore
{
    Q_OBJECT

public:
    explicit MultiGame(QWidget *parent = nullptr);
    int winner = 0; // 记录胜者
    void restart() override;

protected:

signals:

private:
    Snake snake_p2;
    void drawSnake(QPainter *painter) override;
    void timeTick() override;
    void keyPressEvent(QKeyEvent *event)   override;

};

#endif // MULTIGAME_H
