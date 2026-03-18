#include <QLabel>
#include <QApplication>
#include "gamemanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameManager manager;
    return QCoreApplication::exec();
}