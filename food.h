#ifndef FOOD_H
#define FOOD_H

#include <QPoint>
#include <vector>
#include "singlefood.h"

class food
{
public:
    std::vector<singleFood> foods;
    const static int minFood = 2;
    const static int maxFood = 6;
    food();
    void generateFood();
    void reset();

private:
    const int startFood = 3;
    bool notRepeated(const QPoint &point);
};

#endif // FOOD_H
