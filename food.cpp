#include "food.h"

food::food()
{
    for (int i = 0; i < startFood; ++i)
    {
        generateFood();
    }
}

void food::generateFood()
{
    singleFood newFood;
    if (notRepeated(newFood.point))
    {
        foods.push_back(newFood);
    }
    else
    {
        generateFood();
    }
}

bool food::notRepeated(const QPoint &point)
{
    for (const auto& Afood : foods)
    {
        if (point == Afood.point)
        {
            return false;
        }
    }
    return true;
}

void food::reset()
{
    foods.clear();
    for (int i = 0; i < startFood; ++i)
    {
        generateFood();
    }
}