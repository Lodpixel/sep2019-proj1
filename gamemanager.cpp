#include "gamemanager.h"
/*使用 stack 存储不共存的页面，页面及对应页码如下：
0：menu
1：singleGame
2：*/
GameManager::GameManager(QObject *parent) : QObject{parent}
{
    initScenes();
    initStack();
    initElements();
    stack->setCurrentIndex(0);
    stack->show();
    signalConn();
}

void GameManager::startSingleGame()
{
    stack->setCurrentIndex(1);
    singleGame->restart(); // 调用启动函数
    singleGame->setFocus(Qt::OtherFocusReason);
    currentGame = single;
}
void GameManager::startMultiGame()
{
    stack->setCurrentIndex(2);
    multiGame->restart();
    multiGame->setFocus(Qt::OtherFocusReason);
    currentGame = multiple;
    resultShowcase->hide();
}

void GameManager::singleGameOver()
{
    singleOverLay->show();
}

void GameManager::multiGameOver()
{
    multiOverLay->show();
    switch (multiGame->winner)
    {
    case 0:
        resultShowcase->setText("平局！");
        break;
    case 1:
        resultShowcase->setText("P1 获胜！");
        break;
    case 2:
        resultShowcase->setText("P2 获胜！");
        break;
    }
    resultShowcase->show();
}

void GameManager::restartGame()
{
    if (currentGame == single)
    {
        singleOverLay->hide();
        singleGame->restart();
        singleGame->setFocus(Qt::OtherFocusReason);
    }
    if (currentGame == multiple)
    {
        multiOverLay->hide();
        resultShowcase->hide();
        multiGame->restart();
        multiGame->setFocus(Qt::OtherFocusReason);
    }
}

void GameManager::signalConn()
{
    connect(singleOverLay, &DeathOverlay::restartSignal, this, &GameManager::restartGame);
    connect(menu, &Menu::startSingleSignal, this, &GameManager::startSingleGame);
    connect(menu, &Menu::startMultiSignal, this, &GameManager::startMultiGame);
    connect(singleGame, &GameCore::gameOverSignal, this, &GameManager::singleGameOver);
    connect(multiOverLay, &DeathOverlay::restartSignal, this, &GameManager::restartGame);
    connect(multiGame, &GameCore::gameOverSignal, this, &GameManager::multiGameOver);
}

void GameManager::initScenes()
{
    menu = new Menu();
    singleGame = new SingleGame();
    multiGame = new MultiGame();
    singleOverLay = new DeathOverlay(singleGame);
    multiOverLay = new DeathOverlay(multiGame);
    singleOverLay->hide();
    multiOverLay->hide();
}

void GameManager::initStack()
{
    stack = new QStackedWidget();
    stack->setFixedSize(800, 600);
    stack->addWidget(menu);
    stack->addWidget(singleGame);
    stack->addWidget(multiGame);
}

void GameManager::initElements()
{
    resultShowcase = new QLabel(multiOverLay);
    resultShowcase->setAlignment(Qt::AlignCenter);
    resultShowcase->setStyleSheet("color: white; background-color: transparent; font-size: 48px;");
    resultShowcase->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    resultShowcase->setGeometry(220, 250, 400, 100);
}