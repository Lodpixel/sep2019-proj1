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
    void startSingleSignal();
    void startMultiSignal();

private:
    QLabel *title;
    QPushButton *singleButton;
    QPushButton *multiButton;
    void inittitle();
    void initSingleButton();
    void initMultiButton();
    void emitSingleGame();
    void emitMultiGame();
};

#endif // MENU_H
