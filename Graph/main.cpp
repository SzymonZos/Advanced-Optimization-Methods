#include "Dijkstra.hpp"
#include <iostream>
#include <limits>
#include <set>
#include <vector>

std::size_t dijkstra(const std::vector<std::vector<std::size_t>>& graph,
                     std::size_t source,
                     std::size_t target) {
    std::vector<std::size_t> min_distance(
        graph.size(),
        std::numeric_limits<std::size_t>::max());
    min_distance[source] = 0;
    std::set<std::pair<std::size_t, std::size_t>> active_vertices;
    active_vertices.insert({0, source});

    while (!active_vertices.empty()) {
        std::size_t where = active_vertices.begin()->second;
        if (where == target) {
            return min_distance[where];
        }
        active_vertices.erase(active_vertices.begin());
        std::size_t i = 0;
        for (auto ed : graph[where]) {
            if (ed && min_distance[i] > min_distance[where] + ed) {
                active_vertices.erase({min_distance[i], i});
                min_distance[i] = min_distance[where] + ed;
                active_vertices.insert({min_distance[i], i});
            }
            i++;
        }
    }
    return std::numeric_limits<std::size_t>::max();
}

int main() {
    auto dd = dijkstra({{0, 5, 3, 0, 0, 0, 0},
                        {0, 0, 2, 0, 3, 0, 1},
                        {0, 0, 0, 7, 7, 0, 0},
                        {2, 0, 0, 0, 0, 6, 0},
                        {0, 0, 0, 2, 0, 1, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 0, 0}},
                       0,
                       3);
    std::cout << dd;
    return 0;
}
