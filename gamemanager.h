#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QStackedWidget>
#include <QLabel>
#include "gamecore.h"
#include "singlegame.h"
#include "multigame.h"
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
    void startMultiGame();
    void singleGameOver();
    void multiGameOver();
    void restartGame();

private:
    QStackedWidget* stack;
    SingleGame* singleGame;
    MultiGame* multiGame;
    Menu* menu;
    DeathOverlay* singleOverLay;
    DeathOverlay* multiOverLay;
    gameType currentGame;
    QLabel* resultShowcase;
    void signalConn();
    void initScenes();
    void initStack();
    void initElements();
};

#endif // GAMEMANAGER_H
