#ifndef ADVANCED_OPTIMIZATION_METHODS_MODEL_HPP
#define ADVANCED_OPTIMIZATION_METHODS_MODEL_HPP

#include "Types.hpp"
#include "fmt/format.h"
#include <fstream>
#include <regex>
#include <sstream>

namespace AOM {
template<typename T>
class Model {
public:
    Model() = delete;
    ~Model() = default;

    Model(const Model& other) = delete;
    Model& operator=(const Model& other) = delete;

    Model(Model&& other) = delete;
    Model& operator=(Model&& other) = delete;

    explicit Model(std::size_t id) :
        fullPath_{fmt::format("{}/model{}.csv", directoryPath_, id)},
        file_{fullPath_} {
        HandleFileRead();
    }

    Matrix<T> GetModel() const {
        return model_;
    }

private:
    static constexpr const char* directoryPath_ = PROJECT_SOURCE_DIR "/models";
    std::string fullPath_;
    std::ifstream file_;
    Matrix<T> model_{};

    void HandleFileRead() {
        try {
            file_.exceptions(std::ifstream::badbit);
            ReadFromFile();
        } catch (const std::ifstream::failure& exception) {
            fmt::print("Exception: \"{}\" during opening/reading {}\n",
                       exception.what(),
                       fullPath_);
        }
    }

    void ReadFromFile() {
        for (std::string line; std::getline(file_, line);) {
            if (std::regex_search(line, std::regex("[0-9]"))) {
                model_.emplace_back();
                ReadSingleRow(line);
            }
        }
    }

    void ReadSingleRow(const std::string& line) {
        std::istringstream stream{line};
        for (std::string element; std::getline(stream, element, ',');) {
            if (std::regex_match(element, std::regex("^[0-9\\.\r\n]+$"))) {
                T value{};
                std::istringstream{element} >> value;
                model_.back().push_back(value);
            }
        }
    }
};
} // namespace AOM

#endif // ADVANCED_OPTIMIZATION_METHODS_MODEL_HPP
