/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 10/01/2014
 *
 * @section DESCRIPTION
 *
 * KNAPSACK PROBLEM 
 *
 * Class for stroing & handling knapsack data
 */

#include "Knapsack.h"

/**
 * Compute heuristic for all instance values and sort them in decreasing order.
 */
void Knapsack::ComputeHeuristic() {

    for (int i = 0; i < n; i++) {
        this->heuristic.push_back((float) this->items[i].value / (float) this->items[i].weight);
    }
    
}

/**
 * Sorts vector of float values.
 */
std::vector<float> Knapsack::OrderVector(std::vector<float> const& values) {
    std::vector<float> indices(values.size());
    std::iota(begin(indices), end(indices), static_cast<float>(0));

    std::sort(
            begin(indices), end(indices),
            [&](float a, float b) { return values[a] < values[b]; }
            );

    return indices;
}

/**
 * Prints information about given Instance * inst.
 */
void Knapsack::PrintKnapsack() {
    std::string space = " ";

    // priting ID, volume and capacity of knapsack
    std::cout << this->id << space;
    std::cout << this->n<< space;
    std::cout << this->M;

    // printing weights and costs
    for (int i = 0; i < this->n; i++) {
        std::cout << space << this->items[i].weight << space << this->items[i].value; 
    }

    // new line
    std::cout << std::endl;
}



