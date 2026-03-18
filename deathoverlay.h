#ifndef DEATHOVERLAY_H
#define DEATHOVERLAY_H

#include <QWidget>
#include <QPushButton>

class DeathOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit DeathOverlay(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void restartSignal();

private:
    QPushButton *restartBtn = nullptr;
    void initButton();
    void emitRestart();
    void gameOver();
};

#endif // DEATHOVERLAY_H
