#include <iostream>
#include <vector>

#include "statistics.h"


int main() {

    std::vector<IStatistics *> statistics;

    statistics.emplace_back(new Min{});
    statistics.emplace_back(new Max{});
    statistics.emplace_back(new Mean{});
    statistics.emplace_back(new STD{});

    // Handle input data and update Satistics
    double val = 0;
    while (std::cin >> val) {
        for (auto & statistic : statistics) {
            statistic->update(val);
        }
    }

    // Handle invalid input data
    if (!std::cin.eof() && !std::cin.good()) {
        std::cerr << "Invalid input data\n";
        return 1;
    }

    // Print results if any
    for (auto & statistic : statistics) {
        std::cout << statistic->name() << " = " << statistic->eval() << std::endl;
    }

    // Clear memory - delete all objects created by new
    for (auto & statistic : statistics) {
        delete statistic;
    }
    statistics.clear();

    return 0;
}