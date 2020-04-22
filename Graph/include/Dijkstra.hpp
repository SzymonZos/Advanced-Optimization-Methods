#ifndef ADVANCED_OPTIMIZATION_METHODS_DIJKSTRA_HPP
#define ADVANCED_OPTIMIZATION_METHODS_DIJKSTRA_HPP

#include "Types.hpp"
#include <algorithm>
#include <forward_list>
#include <limits>
#include <set>
#include <tuple>

namespace AOM {
template<typename T>
class Dijkstra {
public:
    Dijkstra(const Matrix<T>& graph,
             std::size_t source,
             std::size_t destination) :
        graph_{graph},
        source_{source},
        destination_{destination},
        minDists_(graph_.size(), std::numeric_limits<T>::max()),
        previousVertices_(graph_.size()) {
        Init();
        Run();
    }

    Dijkstra() = delete;
    ~Dijkstra() = default;

    Dijkstra(const Dijkstra& other) = delete;
    Dijkstra& operator=(const Dijkstra& other) = delete;

    Dijkstra(Dijkstra&& other) noexcept = default;
    Dijkstra& operator=(Dijkstra&& other) noexcept = default;

    std::tuple<T, std::forward_list<std::size_t>> GetResult() {
        return {desiredDistance_, route_};
    }

    void Run() {
        while (!activeVertices_.empty()) {
            auto [minimalDistance, currentVertex] = *activeVertices_.begin();
            if (currentVertex == destination_) {
                desiredDistance_ = minimalDistance;
                FindRoute();
                return;
            }
            activeVertices_.erase(activeVertices_.begin());
            EvaluateCurrentVertex(currentVertex);
        }
        desiredDistance_ = std::numeric_limits<std::size_t>::max();
        route_ = {};
    }

private:
    Matrix<T> graph_;
    std::size_t source_;
    std::size_t destination_;

    std::vector<T> minDists_{};
    std::set<std::pair<T, std::size_t>> activeVertices_{};
    std::vector<std::size_t> previousVertices_;

    std::forward_list<std::size_t> route_{};
    T desiredDistance_{};

    void Init() {
        minDists_[source_] = 0;
        activeVertices_.insert({0, source_});
    }

    void EvaluateCurrentVertex(std::size_t vertex) {
        const auto& dists = graph_[vertex];
        for (std::size_t i = 0; i < dists.size(); i++) {
            if (dists[i] && minDists_[i] > minDists_[vertex] + dists[i]) {
                activeVertices_.erase({minDists_[i], i});
                minDists_[i] = minDists_[vertex] + dists[i];
                previousVertices_[i] = vertex;
                activeVertices_.insert({minDists_[i], i});
            }
        }
    }

    void FindRoute() {
        for (std::size_t vertex = destination_; vertex;
             vertex = previousVertices_[vertex]) {
            route_.push_front(vertex);
        }
        route_.push_front(source_);
    }
};
} // namespace AOM

#endif // ADVANCED_OPTIMIZATION_METHODS_DIJKSTRA_HPP
