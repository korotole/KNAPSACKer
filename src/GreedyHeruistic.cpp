/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 10/03/2014
 *
 * @section DESCRIPTION
 *
 * KNAPSACK PROBLEM 
 *
 * Heuristic solution.
 */

#include "GreedyHeruistic.h"

/**
 * Prints vector of float values on line with space between numbers.
 */
void PrintVector(std::vector<float> * vec) {
    for (std::vector<float>::iterator it=vec->begin(); it!=vec->end(); ++it)
        std::cout << *it << " ";

    std::cout << std::endl;
}

/**
 * Solves knapsack problem using heuristic. For all items is computed ratio 
 * of cost/weight, then this values are sorted and chosen first X values which still
 * fits to knapsack.
 */
uint32_t GreedyHeruistic::SolveKnapsack(Knapsack *knapsack, TaskType type){
    std::vector<bool> solution (knapsack->n, 0);
    std::vector<float> order;
    int tmp_cost = 0;
    int32_t tmp_weight = 0;
    uint8_t index;

    knapsack->ComputeHeuristic();

    // sort of computed heuristics
    order = OrderVector(knapsack->heuristic);

    for (auto o_it = order.begin(); o_it != order.end(); ++o_it) {
        index = static_cast<uint8_t>(*o_it);
        tmp_cost += (int) knapsack->items[index].value;
        tmp_weight += (int) knapsack->items[index].weight;

        // is knapsack full?
        if (tmp_weight > knapsack->M)  break;
        if (type == TaskType::DesiciveConstructive && tmp_weight >= knapsack->B) break;
        if (type == TaskType::ExactConstructive && tmp_weight == knapsack->B) break;

        solution.at(index) = 1;
        knapsack->total = tmp_cost;
    }
        knapsack->solution = solution;

    return knapsack->total;
}

/**
 * Sorts vector of float values, from biggest to smallest
 */
std::vector<float> GreedyHeruistic::OrderVector(std::vector<float> const& values) {
    std::vector<float> indices(values.size());
    std::iota(begin(indices), end(indices), static_cast<float>(0));

    std::sort(
            begin(indices), end(indices),
            [&](float a, float b) { return values[a] > values[b]; }
            );

    return indices;
}