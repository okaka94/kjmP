#include "AStar.h"

int main()
{
    AStar::MapGen map;
    map.SetWorldSize({ 8, 5 });
    //                x, y
    map.AddObstacle({ 1, 1 });
    map.AddObstacle({ 1, 2 });
    map.AddObstacle({ 1, 3 });
    map.AddObstacle({ 4, 0 });
    map.AddObstacle({ 4, 1 });
    map.AddObstacle({ 4, 2 });
    map.AddObstacle({ 4, 3 });
    map.AddObstacle({ 2, 3 });
    map.AddObstacle({ 3, 3 });

    auto path = map.FindPath({ 2,2 }, { 6,2 });

    for (auto& index : path)
    {
        std::cout << index.x << " " << index.y << "\n";
    }
    std::cout << "End\n";
}