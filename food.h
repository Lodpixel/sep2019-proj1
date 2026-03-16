#ifndef FOOD_H
#define FOOD_H

#include <QPoint>
#include <vector>

class food
{
public:
    std::vector<QPoint> foods;
    const static int minFood = 1;
    const static int maxFood = 4;
    food();
    void generateFood();

private:
    const int startFood = 2;
    bool notRepeated(const QPoint &point);
};

#endif // FOOD_H
