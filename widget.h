#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;
    void paintEvent(QPaintEvent *event) override;
    const int nodeSize = 20;
    const int columns = 40;
    const int rows = 30;

private:
    void drawGrid(QPainter *painter); // 绘制网格
    void drawSnake(QPainter *painter); // 绘制蛇
    void drawFood(QPainter *painter); // 绘制食物
};
#endif // WIDGET_H
