#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include "snake.h"
#include "food.h"
#include "gamecore.h"

class SingleGame : public GameCore
{
    Q_OBJECT

public:
    explicit SingleGame(QWidget *parent = nullptr);
    ~SingleGame() override;
    
protected:

private:
    void timeTick() override;
};

#endif // SINGLEGAME_H