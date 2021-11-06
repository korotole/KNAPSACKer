/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 */

#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <numeric>

#include <stdlib.h>

#include "Common.h"

class Knapsack {

  public:

    int16_t id = 0; // ID of instance
    int32_t B = 0;  // požadovana minimální cena
    uint8_t n = 0;  // počet věcí
    int32_t M = 0;  // kapacita batohu    

    int32_t total = 0;  // sum of all item values
    
    Item *items = nullptr;

    // auxiliary variables
    std::vector<int> appr_cost = { };     // approximated cost of all items
    std::vector<bool> solution = { };    // solution for current items
    std::vector<float> heuristic = { };  // computed heuristic value (cost/weight)

    /**
     * Constructor. 
     *
     * Checks if given file name exist, parse lines of that file and creates instances.
     *
     * @param  file_name  name of file with instances
     */
    Knapsack(uint16_t id, int32_t B, uint8_t n, int32_t M) : id(id), B(B), n(n), M(M) { 
        this->items = new Item[static_cast<int>(this->n)] ();    // allocate array of items of desired size
    };
    /**
     * Destructor.
     *
     * Deallocates members of vector all_instances.
     */
    ~Knapsack() {
        delete[] items;
    };

    /**
     * Getter of max items which can be selected for knapsack.
     *
     * @return  number of items
     */
    int GetMaxItems();

    /**
     * Getter of knapsack volume.
     *
     * @return  volume
     */
    int GetVolume();

    /**
     * Getter of knapsack capacity.
     *
     * @return  capacity
     */
    int GetCapacity();

    /**
     * Prints solutions of all instances.
     */
    void PrintSolutions();

    /**
     * Compute heuristic for all instance values and sort them in decreasing order.
     */
    void ComputeHeuristic();

    /**
     * Sorts vector of float values.
     *
     * @param  values  vector of float values
     * @return         vector of indexes according to sorted values
     */
    std::vector<float> OrderVector(std::vector<float> const& values);

    void PrintKnapsack(); 

};

#endif //INSTANCE_HH
