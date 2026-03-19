#include "menu.h"

Menu::Menu(QWidget *parent) : QWidget{parent}
{
    inittitle();
    initSingleButton();
    initMultiButton();
}

void Menu::inittitle()
{
    title = new QLabel("贪吃蛇_LoD ver.", this);
    title->move(300, 150);
    title->show();
}

void Menu::initSingleButton()
{
    singleButton = new QPushButton("单人模式", this);
    singleButton->move(300, 400);
    singleButton->show();
    connect(singleButton, &QPushButton::clicked, this, &Menu::emitSingleGame);
}

void Menu::initMultiButton()
{
    multiButton = new QPushButton("双人模式", this);
    multiButton->move(300, 500);
    multiButton->show();
    connect(multiButton, &QPushButton::clicked, this, &Menu::emitMultiGame);
}

void Menu::emitSingleGame()
{
    emit startSingleSignal();
}

void Menu::emitMultiGame()
{
    emit startMultiSignal();
}