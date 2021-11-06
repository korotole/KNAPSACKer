/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 */

#ifndef DYNAMIC_H
#define DYNAMIC_H

#include "Knapsack.h"

#define BEGIN       0

struct Cell {
    uint32_t cost;
    uint32_t weight;
    int32_t weight_index;
    Cell *forward_first;
    Cell *forward_second;

    // 0 left; first
    // 1 bottom left; second
    int direction;
};

class Dynamic {
  public:
    static uint32_t SolveKnapsack(Knapsack *knapsack, TaskType type);

  private:

    // solve knapsack problem via Dynamic programming Intelligently, storing the items configuration
    static uint32_t SolveIDynamic(Knapsack *knapsack, TaskType type);

    // solve knapsack problem via Dynamic programming Rapidly, stores merely result
    static uint32_t SolveRDynamic(Knapsack *knapsack, TaskType type);

    static std::vector<std::vector<Cell *>> CreateNetwork(Knapsack *knapsack, int32_t capacity);
    static void SolveNetwork(Knapsack *knapsack, std::vector<std::vector<Cell *>> * table, TaskType type);
    static void DeleteTable(std::vector<std::vector<Cell*>> * table);
    static std::vector<bool> FindPath(Cell * cell);
    static Cell *CreateCell(int wi);
    static Cell *ExistCell(std::vector<Cell *> * column, int weight);
};

#endif //DYNAMIC_H