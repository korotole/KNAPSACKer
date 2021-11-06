/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 */

#include "Knapsack.h"

class BruteForce {
  public:
    static uint32_t SolveKnapsack(Knapsack *knapsack, TaskType type);

  private:

    // solve knapsack problem via Brute Force Intelligently, storing the items configuration
    static void SolveIBruteForce(Knapsack *knapsack, TaskType type);

    // solve knapsack problem via Brute Force Rapidly, stores merely result
    static uint32_t SolveRBruteForce(uint8_t n, int32_t M, Item *items, TaskType type, int32_t B);

    static std::vector<std::vector<bool>> * GenerateCombinations(int, int);
    static std::vector<bool> Evaluate(Knapsack *knapsack, TaskType type, std::vector<std::vector<bool>> *combinations);
    static Item EvaluateCombination(Knapsack *knapsack, TaskType type, std::vector<bool> *combinations);
};