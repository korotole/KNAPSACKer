/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 */

#ifndef HEURISTIC_HH
#define HEURISTIC_HH

#include "Knapsack.h"

class GreedyHeruistic {
  public:
    static uint32_t SolveKnapsack(Knapsack *knapsack, TaskType type);

  private:
    /**
     * Solves knapsack problem using heuristic. For all items is computed ratio 
     * of cost/weight, then this values are sorted and chosen first X values which still
     * fits to knapsack.
     *
     * @param  inst  pointer to Instances object
     */
    static void SolveHeuristic(Knapsack *knapsack);

    /**
     * Sorts vector of float values.
     *
     * @param  values  vector of float values
     * @return         vector of indexes according to sorted values
     */
    static std::vector<float> OrderVector(std::vector<float> const& values);
};

#endif //HEURISTIC_HH