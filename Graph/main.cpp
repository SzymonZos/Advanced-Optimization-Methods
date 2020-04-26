#include "Dijkstra.hpp"
#include "GenericOstreamOperators.hpp"
#include "Model.hpp"
#include <algorithm>
#include <iostream>

int main() {
    AOM::Model<std::size_t> rawModel{0};
    auto model = rawModel.GetModel();
    using SrcDestVector = std::vector<std::pair<std::size_t, std::size_t>>;
    SrcDestVector srcDestVec{{14, 0},
                             {0, 14},
                             {4, 5},
                             {3, 3},
                             {10, 2},
                             {0, 0},
                             {12, 30}};
    std::for_each(srcDestVec.begin(), srcDestVec.end(), [&](const auto& pair) {
        const auto [source, destination] = pair;
        AOM::Dijkstra<std::size_t> dijkstra{model, source, destination};
        auto [distance, route] = dijkstra.GetResult();
        std::cout << "source: " << source << ", destination: " << destination
                  << "\nroute: " << route << ", distance: " << distance
                  << "\n\n";
    });
    return 0;
}
