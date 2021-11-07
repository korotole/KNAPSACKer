/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 07/11/2021
 */

#ifndef FPTAS_H 
#define FPTAS_H 

#include <bitset>
#include <stdlib.h>

#include "Common.h"
#include "Knapsack.h"
#include "Dynamic.h"

#define BITS        20

typedef std::bitset<BITS> bit;

class FPTAS {
  public:
    static uint32_t SolveKnapsack(Knapsack *knapsack, TaskType type);

  private:
    static void ReducePrecision(Knapsack *knapsack);
    static bit ReducePrecision(int n, int p);
    static int bit2int(bit b);
    static bit CreateMask(int l);

    static std::vector<std::vector<Item *>> CreateNetwork(Knapsack *knapsack, int capacity);
    static Item* FindCostWeight(std::vector<std::vector<Item*>>* table, int capacity);
    static std::vector<bool> GetSolutionPath(std::vector<std::vector<Item *>> * table, Item * item, Knapsack *knapsack); 
    static int GetSumCost(Knapsack *knapsack, std::vector<bool> solution);
    static std::vector<bool> RecoverPath(std::vector<bool> * path, int length);
    static void DeleteTable(std::vector<std::vector<Item *>> & table);

    static Item * CreateItem(int c, int w, Item * p_c);
    static Item * FindNextItem(std::vector<Item *> * column, int weight);
    static bool ExistItem(std::vector<Item *> & column, int cost, int weight);
    static Item * CompareItems(Item * c1, Item * c2);
    static bool TestItemWeight(Item * c, int capacity);
    static bool EqualItem(Item * item, int cost, int weight);
};

#endif //FPTAS_H 