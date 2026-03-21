#include "singlefood.h"
#include "config.h"

std::mt19937 &singleFood::rng()
{
    static std::mt19937 eng(std::random_device{}());
    return eng;
}

int singleFood::randInt(int l, int r)
{
    std::uniform_int_distribution<int> dist(l, r);
    return dist(rng());
}

singleFood::singleFood()
{
    int randomVal = randInt(0, 9);
    int randomX = randInt(0, GameConfig::columns - 1);
    int randomY = randInt(0, GameConfig::rows - 1);

    switch (randomVal)
    {
    case 1:
        type = chaos;
        break;
    default:
        type = normal;
        break;
    }

    point = QPoint(randomX * GameConfig::nodeSize, randomY * GameConfig::nodeSize);
}


