#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QStackedWidget>
#include "gamecore.h"
#include "singlegame.h"
#include "menu.h"
#include "deathoverlay.h"

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);
    enum gameType
    {
        single,
        multiple
    };

signals:

private slots:
    void startSingleGame();
    void singleGameOver();
    void restartGame();

private:
    QStackedWidget* stack;
    SingleGame* singleGame;
    Menu* menu;
    DeathOverlay* singleOverLay;
    gameType currentGame;
    void signalConn();
    void initScenes();
    void initStack();
};

#endif // GAMEMANAGER_H
