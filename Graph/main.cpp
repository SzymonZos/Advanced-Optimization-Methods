#include "Dijkstra.hpp"
#include <iostream>

int main() {
    Dijkstra<std::size_t> dijkstra({{0, 5, 3, 0, 0, 0, 0},
                                    {0, 0, 2, 0, 3, 0, 1},
                                    {0, 0, 0, 7, 7, 0, 0},
                                    {2, 0, 0, 0, 0, 6, 0},
                                    {0, 0, 0, 2, 0, 1, 0},
                                    {0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 1, 0, 0}},
                                   0,
                                   3);
    auto [distance, route] = dijkstra.GetResult();
    std::cout << distance;
    return 0;
}
