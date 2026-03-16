#ifndef FOOD_H
#define FOOD_H

#include <QPoint>
#include <vector>

class food
{
public:
    std::vector<QPoint> foods;
    const int minFood = 1;
    const int maxFood = 4;
    food();
    void generateFood();

private:
    const int startFood = 2;
    bool notRepeated(const QPoint &point);
};

#endif // FOOD_H
