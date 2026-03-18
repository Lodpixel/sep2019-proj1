#include "deathoverlay.h"
#include "config.h"
#include <QPainter>
#include <QLabel>

DeathOverlay::DeathOverlay(QWidget *parent) : QWidget{parent}
{
    setFixedSize(800, 600);
    initButton();
}

void DeathOverlay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 160));
    painter.drawRect(0, 0, GameConfig::nodeSize * GameConfig::columns, GameConfig::nodeSize * GameConfig::rows);

    painter.setPen(Qt::white);
    painter.setFont(QFont("Microsoft YaHei", 40));
    painter.drawText(300, 200, "游戏结束！");
    restartBtn->show();
}

void DeathOverlay::initButton()
{
    restartBtn = new QPushButton("重新开始", this);
    restartBtn->setStyleSheet("color: white;");
    restartBtn->move(360, 400);
    restartBtn->resize(100, 40);
    connect(restartBtn, &QPushButton::clicked, this, &DeathOverlay::emitRestart);
}

void DeathOverlay::emitRestart()
{
    emit restartSignal();
}

void DeathOverlay::gameOver()
{
    this->update();
}