#include "GenericOstreamOperators.hpp"
#include "GeneticAlgorithm.hpp"
#include <iostream>

auto FirstTask() {
    constexpr std::size_t noAlleles = 4;
    constexpr std::size_t noParents = 250;
    constexpr auto noOffspring = static_cast<std::size_t>(0.8 * noParents);
    const std::size_t tMax = 1000;
    constexpr DblArray<4> weights{2, 1, 4, 5};
    constexpr DblArray<4> benefits{3, 2, 6, 8};
    GeneticAlgorithm<noOffspring, noAlleles, noParents> algorithm{tMax,
                                                                  weights,
                                                                  benefits,
                                                                  9};
    return algorithm.GetResult();
}

int main() {
    auto [result, minCostValue] = FirstTask();
    std::reverse(result.begin(), result.end());
    std::cout << "Optimal solution is: " << result
              << " with total benefit: " << minCostValue;
    return 0;
}