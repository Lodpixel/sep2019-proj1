#include "menu.h"

Menu::Menu(QWidget *parent) : QWidget{parent}
{
    inittitle();
    initSingleButton();
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
    connect(singleButton, &QPushButton::clicked, this, &Menu::emitStartGame);
}

void Menu::emitStartGame()
{
    emit startGameSignal();
}