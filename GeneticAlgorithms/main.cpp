#include "GenericOstreamOperators.hpp"
#include "GeneticAlgorithm.hpp"
#include "Timer.hpp"
#include <iostream>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

#define GENETIC_ALGORITHM(noParents, n) \
    { \
        constexpr auto noOffspring = static_cast<std::size_t>((n) * \
                                                              (noParents)); \
        auto [result, \
              benefit] = RunAlgorithm<noOffspring, noParents>(tMax, \
                                                              weights, \
                                                              benefits, \
                                                              maxWeight); \
        logger->info("{}, {}, {}", benefit, noParents, noOffspring); \
        PrintResults(result, benefit); \
    }

template<std::size_t noAlleles>
void PrintResults(IntArray<noAlleles>& result, double minCostValue) {
    std::reverse(result.begin(), result.end());
    std::cout << "Optimal solution is: " << result
              << " with total benefit: " << minCostValue << '\n';
}

template<std::size_t noOffspring, std::size_t noParents, std::size_t noAlleles>
auto RunAlgorithm(std::size_t tMax,
                  const DblArray<noAlleles>& weights,
                  const DblArray<noAlleles>& benefits,
                  double maxWeight) {
    Timer timer;
    GeneticAlgorithm<noOffspring, noAlleles, noParents> algorithm{tMax,
                                                                  weights,
                                                                  benefits,
                                                                  maxWeight};
    return algorithm.GetResult();
}

void Demo() {
    constexpr std::size_t noAlleles = 4;
    constexpr std::size_t noParents = 250;
    constexpr auto noOffspring = static_cast<std::size_t>(0.8 * noParents);
    const std::size_t tMax = 100;
    constexpr DblArray<noAlleles> weights{2, 1, 4, 5};
    constexpr DblArray<noAlleles> benefits{3, 2, 6, 8};
    GeneticAlgorithm<noOffspring, noAlleles, noParents> algorithm{tMax,
                                                                  weights,
                                                                  benefits,
                                                                  9};
    auto [result, minCostValue] = algorithm.GetResult();
    PrintResults(result, minCostValue);
}

void FirstTask() {
    constexpr std::size_t noAlleles = 10;
    const std::size_t tMax = 40;
    const double maxWeight = 67;
    DblArray<noAlleles> weights{23, 26, 20, 18, 32, 27, 29, 26, 30, 27};
    DblArray<noAlleles>
        benefits{505, 352, 458, 220, 354, 414, 498, 545, 473, 543};
    auto logger = spdlog::rotating_logger_mt("FirstTask",
                                             "logs/FirstTask.csv",
                                             1048576 * 5,
                                             1,
                                             true);
    logger->info("benefit, noParents, noOffspring");
    GENETIC_ALGORITHM(30, 0.5)
    GENETIC_ALGORITHM(30, 0.7)
    GENETIC_ALGORITHM(30, 0.9)
    GENETIC_ALGORITHM(50, 0.5)
    GENETIC_ALGORITHM(50, 0.7)
    GENETIC_ALGORITHM(50, 0.9)
    GENETIC_ALGORITHM(100, 0.5)
    GENETIC_ALGORITHM(100, 0.7)
    GENETIC_ALGORITHM(100, 0.9)
}

void SecondTask() {
    constexpr std::size_t noAlleles = 15;
    const std::size_t tMax = 40;
    const double maxWeight = 96;
    DblArray<noAlleles>
        weights{23, 26, 20, 18, 32, 27, 29, 26, 30, 27, 29, 23, 24, 19, 25};
    DblArray<noAlleles>
        benefits{50, 35, 45, 22, 35, 41, 49, 54, 47, 54, 23, 56, 44, 59, 33};
    auto logger = spdlog::rotating_logger_mt("SecondTask",
                                             "logs/SecondTask.csv",
                                             1048576 * 5,
                                             1,
                                             true);
    logger->info("benefit, noParents, noOffspring");
    GENETIC_ALGORITHM(30, 0.5)
    GENETIC_ALGORITHM(30, 0.7)
    GENETIC_ALGORITHM(30, 0.9)
    GENETIC_ALGORITHM(50, 0.5)
    GENETIC_ALGORITHM(50, 0.7)
    GENETIC_ALGORITHM(50, 0.9)
    GENETIC_ALGORITHM(100, 0.5)
    GENETIC_ALGORITHM(100, 0.7)
    GENETIC_ALGORITHM(100, 0.9)
}

int main() {
    Demo();
    FirstTask();
    SecondTask();
    return 0;
}