/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 */

#ifndef BRANCHBOUND_H
#define BRANCHBOUND_H

#include "Knapsack.h"

#include <queue>


#define EMPTY      -1

class BranchBound {
  public:
    static uint32_t SolveKnapsack(Knapsack *knapsack, TaskType type);
  
  private:
    static uint32_t SolveIBranchBound(Knapsack *knapsack, TaskType type);
    static uint32_t SolveRBranchBound(uint8_t n, int32_t M, Item *items, TaskType type, int32_t B);

    static std::vector<bool> Evaluate(Knapsack *Knapsack, TaskType type);
    static std::vector<bool> CreateEmptyKnapsack(uint8_t size);
    static uint32_t ComputeCurrentCost(std::vector<bool> * distribution, Knapsack *knapsack);
    static uint32_t ComputeRemainingCost(std::vector<bool> * distribution, Knapsack *knapsack);
    static uint32_t ComputeCurrentWeight(std::vector<bool> * distribution, Knapsack *knapsack);
    static int8_t GetPosition(std::vector<bool> * inst_item);
    static std::vector<bool> NextItem(std::vector<bool> * inst_item, uint8_t position);
};

#endif //BRANCHBOUND_HH