#include "food.h"
#include "config.h"
#include <random>
#include <ctime>
#include <QPoint>

food::food()
{
    for (int i = 0; i < startFood; ++i)
    {
        generateFood();
    }
}

void food::generateFood()
{
    // 生成随机的坐标
    static std::mt19937 maskEngine(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> xRange(0, GameConfig::columns - 1);
    std::uniform_int_distribution<int> yRange(0, GameConfig::rows - 1);
    int randomX = xRange(maskEngine);
    int randomY = yRange(maskEngine);

    QPoint point(randomX * GameConfig::nodeSize, randomY * GameConfig::nodeSize);
    if (notRepeated(point))
    {
        foods.push_back(point);
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
        if (point == Afood)
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