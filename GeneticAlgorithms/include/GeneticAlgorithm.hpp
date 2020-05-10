#ifndef GENETICALGORITHMS_GENETICALGORITHM_HPP
#define GENETICALGORITHMS_GENETICALGORITHM_HPP

#include "Types.hpp"
#include <algorithm>
#include <functional>
#include <map>
#include <random>
#include <tuple>

template<std::size_t noOffspring, std::size_t noAlleles, std::size_t noParents>
class GeneticAlgorithm {
public:
    GeneticAlgorithm(std::size_t tMax,
                     DblArray<noAlleles> weights,
                     DblArray<noAlleles> benefits,
                     double maxWeight) :
        tMax_{tMax},
        weights_{std::move(weights)},
        benefits_{std::move(benefits)},
        maxWeight_{maxWeight} {
        Run();
    }

    GeneticAlgorithm() = delete;
    ~GeneticAlgorithm() = default;

    void Run() {
        CreateInitialPopulation();
        for (std::size_t i = 0; i < tMax_; i++) {
            parentCostValues_ = CalculateCostValues(parents_);
            GenerateOffspring(SelectParents());
            MutateOffspring();
            offspringCostValues_ = CalculateCostValues(offspring_);
            ReplacePopulation();
        }
    }

    std::tuple<IntArray<noAlleles>, double> GetResult() {
        return {parents_[0], minCostValue_};
    }

private:
    using Compare = std::greater<double>;

    std::size_t tMax_;
    DblArray<noAlleles> weights_;
    DblArray<noAlleles> benefits_;
    double maxWeight_;

    std::mt19937 rng_{std::random_device{}()};
    std::uniform_int_distribution<> offspringDist_{0, noOffspring - 1};
    std::uniform_int_distribution<> allelesDist_{0, noAlleles - 1};
    std::uniform_int_distribution<> binaryDist_{0, 1};

    IntMatrix<noAlleles, noParents> parents_{};
    DblArray<noParents> parentCostValues_{};
    IntMatrix<noAlleles, noOffspring> offspring_{};
    DblArray<noOffspring> offspringCostValues_{};
    std::multimap<double, IntArray<noAlleles>, Compare> sortedPopulation_{};
    double minCostValue_{};

    template<std::size_t size>
    auto CalculateCostValues(const IntMatrix<noAlleles, size>& population) {
        DblArray<size> costValues = {};
        std::size_t idx = 0;
        for (auto& chromosome : population) {
            auto weights = chromosome * weights_;
            auto totalWeight = std::accumulate(weights.begin(),
                                               weights.end(),
                                               0.0);
            auto benefits = chromosome * benefits_;
            auto totalBenefit = std::accumulate(benefits.begin(),
                                                benefits.end(),
                                                0.0);
            costValues[idx++] = totalWeight <= maxWeight_ ? totalBenefit : 0;
        }
        return costValues;
    }

    void CreateInitialPopulation() {
        for (auto& parent : parents_) {
            double totalWeight{};
            do {
                std::generate(parent.begin(), parent.end(), [&] {
                    return binaryDist_(rng_);
                });
                auto weights = parent * weights_;
                totalWeight = std::accumulate(weights.begin(),
                                              weights.end(),
                                              0.0);
            } while (totalWeight > maxWeight_);
        }
    }

    auto SelectParents() {
        IntMatrix<noAlleles, noOffspring> chosenParents = {};
        auto maxCost = std::max_element(parentCostValues_.begin(),
                                        parentCostValues_.end());
        double ts = std::accumulate(
            parentCostValues_.begin(),
            parentCostValues_.end(),
            0.0,
            [&](double prev, double curr) { return prev + *maxCost - curr; });
        std::uniform_real_distribution<> realDistribution(0.0, ts);
        for (auto& chosenParent : chosenParents) {
            double randomNumber = realDistribution(rng_);
            double ti = 0;
            for (std::size_t i = 0; i < noParents; i++) {
                ti += *maxCost - parentCostValues_[i];
                if (ti >= randomNumber) {
                    chosenParent = parents_[i];
                    break;
                }
            }
        }
        return chosenParents;
    }

    template<typename T>
    void GenerateOffspring(T&& parents) {
        IntArray<2> index = {};
        for (std::size_t i = 0; i < noOffspring; i += 2) {
            std::generate(index.begin(), index.end(), [&] {
                return offspringDist_(rng_);
            });
            offspring_[i] = parents[index[0]];
            offspring_[i + 1] = parents[index[1]];
            auto crossover = static_cast<std::size_t>(allelesDist_(rng_));
            for (std::size_t j = 0; j < crossover; j++) {
                std::swap(offspring_[i][j], offspring_[i + 1][j]);
            }
        }
    }

    void MutateOffspring() {
        for (auto& child : offspring_) {
            auto index = static_cast<std::size_t>(allelesDist_(rng_));
            child[index] = !child[index];
        }
    }

    void SortPopulation() {
        for (std::size_t i = 0; i < noParents; i++) {
            sortedPopulation_.insert({parentCostValues_[i], parents_[i]});
            if (i < noOffspring) {
                sortedPopulation_.insert(
                    {offspringCostValues_[i], offspring_[i]});
            }
        }
    }

    void ReplacePopulation() {
        SortPopulation();
        auto it = sortedPopulation_.begin();
        std::generate(parents_.begin(), parents_.end(), [&] {
            return (it++)->second;
        });
        minCostValue_ = sortedPopulation_.begin()->first;
        sortedPopulation_.clear();
    }
};

#endif // GENETICALGORITHMS_GENETICALGORITHM_HPP
