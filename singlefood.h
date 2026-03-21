#ifndef SINGLEFOOD_H
#define SINGLEFOOD_H

#include <QPoint>
#include <random>

class singleFood
{
public:
    singleFood();
    enum foodType
    {
        normal,
        chaos
    };
    QPoint point;
    foodType type;

private:
    static std::mt19937& rng();
    static int randInt(int l, int r);
};

#endif // SINGLEFOOD_H
