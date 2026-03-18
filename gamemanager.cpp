#include "gamemanager.h"
#include "deathoverlay.h"
/*使用 stack 存储不共存的页面，页面及对应页码如下：
0：menu
1：singleGame
2：*/
GameManager::GameManager(QObject *parent) : QObject{parent}
{
    initScenes();
    initStack();
    stack->setCurrentIndex(0);
    stack->show();
    signalConn();
}

void GameManager::startSingleGame()
{
    stack->setCurrentIndex(1);
    currentGame = single;
}

void GameManager::singleGameOver()
{
    singleOverLay->show();
}

void GameManager::restartGame()
{
    if (currentGame == single)
    {
        singleOverLay->hide();
        singleGame->restart();
    }
}

void GameManager::signalConn()
{
    connect(singleOverLay, &DeathOverlay::restartSignal, this, &GameManager::restartGame);
    connect(menu, &Menu::startGameSignal, this, &GameManager::startSingleGame);
    connect(singleGame, &SingleGame::gameOverSignal, this, &GameManager::singleGameOver);
}

void GameManager::initScenes()
{
    menu = new Menu();
    singleGame = new SingleGame();
    singleOverLay = new DeathOverlay(singleGame);
}

void GameManager::initStack()
{
    stack = new QStackedWidget();
    stack->setFixedSize(800, 600);
    stack->addWidget(menu);
    stack->addWidget(singleGame);
}