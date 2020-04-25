#include "Dijkstra.hpp"
#include "GenericOstreamOperators.hpp"
#include "Model.hpp"
#include <iostream>

int main() {
    AOM::Model<std::size_t> rawModel{0};
    auto model = rawModel.GetModel();
    AOM::Dijkstra<std::size_t> dijkstra{model, 14, 0};
    auto [distance, route] = dijkstra.GetResult();
    std::cout << "route: " << route << ", distance: " << distance << std::endl;
    return 0;
}
