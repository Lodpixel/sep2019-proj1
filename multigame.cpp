#include "multigame.h"

MultiGame::MultiGame(QWidget *parent) : QWidget{parent}
{
    gameTimer = new QTimer(this);
    foodTimer = new QTimer(this);
}


