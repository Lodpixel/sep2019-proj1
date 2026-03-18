#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);

signals:
    void startGameSignal();

private:
    QLabel *title;
    QPushButton *singleButton;
    void inittitle();
    void initSingleButton();
    void emitStartGame();
};

#endif // MENU_H
