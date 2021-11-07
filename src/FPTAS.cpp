/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 07/11/2021
 *
 * @section DESCRIPTION
 *
 * KNAPSACK PROBLEM 
 *
 * FPTAS solution.
 */

#include "FPTAS.h"

/**
 * Solves given instances by FPTAS method.
 *
 * @param   knapsack   knapsack interface 
 * @param   precision  number of LSB which we can ommit
 */
uint32_t FPTAS::SolveKnapsack(Knapsack *knapsack, TaskType type) {

    ReducePrecision(knapsack);

    // create and compute network
    std::vector<std::vector<Item*>> table = CreateNetwork(knapsack, knapsack->M);
    
    // find final weight and value
    Item *c_w = FindCostWeight(&table, knapsack->M);

    knapsack->solution = GetSolutionPath(&table, c_w, knapsack);


    // set the best value of particular knapsack configuration
    knapsack->total = GetSumCost(knapsack, knapsack->solution);

    // deallocate all nodes
    DeleteTable(table);

    return (uint32_t) knapsack->total;
}

std::vector<std::vector<Item *>> FPTAS::CreateNetwork(Knapsack *knapsack, int capacity) {
    std::vector<Item*> column;
    int tmp_value;
    int tmp_weight;
    std::vector<std::vector<Item *>> table;

    Item * tmp_item = NULL;
    std::vector<int> values = knapsack->appr_cost;
    std::vector<int> weights;

    for(uint8_t i = 0; i < knapsack->n; i++) {
        weights.push_back(knapsack->items[i].weight);
    }       

    Item * init_item = CreateItem( values.front(), 
                                   weights.front(),
                                   NULL );

    std::vector<Item *> init_col = {init_item};
    table.insert(table.begin(), init_col); 

    // +1 because we have already used the first item in creating network
    auto c = values.begin()+1;
    for (auto w = weights.begin()+1; w != weights.end(); ++w, ++c) {

        std::vector<Item*> tmp_column;
        column = table.front();

        for (auto col = column.begin(); col != column.end(); ++col) {
            tmp_value = (*col)->value;
            tmp_weight = (*col)->weight;

            // recreate the same item
            if (!ExistItem(tmp_column, tmp_value, tmp_weight)) {
                tmp_item = CreateItem(tmp_value, tmp_weight, *col);
                tmp_column.push_back(tmp_item);
            }

            // create new item
            if (!ExistItem(tmp_column, *c, *w)) {
                tmp_item = CreateItem((*c), (*w), NULL);
                tmp_column.push_back(tmp_item);
            }

            // summed item
            // add weight and value to the current examined item
            if (!ExistItem(tmp_column, tmp_value+(*c), tmp_weight+(*w))) {
                tmp_item = CreateItem(tmp_value+(*c), tmp_weight+(*w), NULL);
                tmp_column.push_back(tmp_item);
            }
        }

        table.insert(table.begin(), tmp_column); 
    }


    return table;
}

/**
 * Sums real values of output configuration.
 *
 * @param   knapsack 
 * @param   solution  
 * @return            sum of values from final configuration
 */
int FPTAS::GetSumCost(Knapsack *knapsack, std::vector<bool> solution) {
    int sum_value = 0;

    auto b_it = solution.begin();
    for (uint8_t i = 0; i < knapsack->n; ++i, ++b_it) {
        if (*b_it) sum_value += knapsack->items[i].value;
    }

    return sum_value;
}


/**
 * Deallocated all items from given table.
 *
 * @param   table
 */
void FPTAS::DeleteTable(std::vector<std::vector<Item *>> & table) {
    for (auto t_it = table.begin(); t_it != table.end(); ++t_it)
        for (auto c_it = t_it->begin(); c_it != t_it->end(); ++c_it)
            delete *c_it;
}

/**
 * Creates and initializes item.
 *
 * @param  c  value
 * @param  w  weight
 * @return    pointer to new created item
 */
Item * FPTAS::CreateItem(int c, int w, Item * p_c) {
    auto item = new Item();

    item->value = c;
    item->weight = w;
    item->forward = p_c;

    return item;
}

/**
 * Finds the best combination of value and weight in the last column 
 * of created network/table.
 *
 * @param   table     generated network
 * @param   capacity  maximum capacity fo knapsack
 * @return            item containin the best combination of weight and value
 */
Item * FPTAS::FindCostWeight(std::vector<std::vector<Item*>>* table, int capacity) {
    std::vector<Item*> last_column = table->front();

    Item * tmp_best_item = NULL;

    for (auto c_it = last_column.begin(); c_it != last_column.end(); ++c_it) {
       if (TestItemWeight(*c_it, capacity)) {

        if (tmp_best_item == NULL) // the first occasion of solution
            tmp_best_item = *c_it;
        else // not the first occasion of solution
            tmp_best_item = CompareItems(tmp_best_item, *c_it);
       }
    }

    return tmp_best_item;
}

/**
 * Compares two items in order to find the best solution.
 * Assumes that weight of both items does not exceed the maximum weight.
 *
 * @param   c1  the first tested item
 * @param   c2  the second tested item
 * @return      the best item selected from tested items
 */
Item * FPTAS::CompareItems(Item * c1, Item * c2) { return (c1->value > c2->value) ? c1 : c2; }

/**
 * Tests if the weight of given item does not exceed desired maximum allowed weight.
 *
 * @param   c           tested item
 * @param   max_weight  maximum weight of knapsack
 * @return              boolean decision about weight of knapsack
 */
bool FPTAS::TestItemWeight(Item * c, int capacity) { return (c->weight <= capacity); }

/**
 * Goes through the network and follows the path from the best solution to the beginning.
 *
 * @param   table
 * @param   item
 * @param   knapsack 
 * @return         solution path
 */
std::vector<bool> FPTAS::GetSolutionPath(std::vector<std::vector<Item *>> * table, Item * item, Knapsack *knapsack) {
    uint8_t widx = knapsack->n - (uint8_t) 1;
    auto col_it = table->begin()+1;
    int tmp_weight = item->weight;

    Item * forward_item = item;

    std::vector<bool> path;

    while (tmp_weight > 0) {
        if (forward_item->forward == NULL) {
            path.insert(path.begin(), 1);

            tmp_weight -= knapsack->items[widx].weight; 
            if (tmp_weight <= 0)
                break;

            forward_item = FindNextItem(&(*col_it), tmp_weight);
        }
        else {
            path.insert(path.begin(), 0);
            forward_item = forward_item->forward;
        }

        --widx;
        ++col_it;
    }

    path = RecoverPath(&path, (int) knapsack->n);

    return path;
}

/**
 * Finds the next item, which can be connected to current item with given weight, 
 * in lower level of network.
 *
 * @param   column  column of the network
 * @param   weight  searched weight of item
 * @return          item with the highest value and desired weight
 */
Item * FPTAS::FindNextItem(std::vector<Item *> * column, int weight) {
    Item * tmp_item = NULL;

    for (auto col_it = column->begin(); col_it != column->end(); ++col_it) {

        if ((*col_it)->weight == weight) {
            if (tmp_item == NULL) 
                tmp_item = *col_it;
            else
                tmp_item = CompareItems(tmp_item, *col_it);
        }
    }

    return tmp_item;
}

/**
 * Searches for a item with specific parameters in column.
 *
 * @param   column
 * @param   value
 * @param   weight  
 * @return          true if column contains item with tested value and weight, 
 *                  otherwise false
 */
bool FPTAS::ExistItem(std::vector<Item *> & column, int value, int weight) {
    for (auto c_it = column.begin(); c_it != column.end(); ++c_it)
        if (EqualItem(*c_it, value, weight))
            return true;
    
    return false;
}

/**
 * Checks if item contain given value and weight.
 *
 * @param   item
 * @param   value
 * @param   weight  
 * @return          true if item contains tested value and weight, otherwise false
 */
bool FPTAS::EqualItem(Item * item, int value, int weight) { return (item->value == value && item->weight == weight); }

/**
 * Adds binary zeros to given path to extend binary solution to desired length.
 *
 * @param   path
 * @param   length  
 * @return          rovered path with right length of binary vector
 */
std::vector<bool> FPTAS::RecoverPath(std::vector<bool> * path, int length) {
    int d;
    std::vector<bool> full_path = *path;

    if ((d = length - path->size()) != 0)
        for (int i = 0; i < d; ++i) full_path.insert(full_path.begin(), 0);

    return full_path;
}

/**
 * Reduces precison of value in all later examined instances.
 *
 * @param   knapsack
 */
void FPTAS::ReducePrecision(Knapsack *knapsack) {
    // value
    for (int i = 0; i < knapsack->n; i++)
        knapsack->appr_cost.push_back(bit2int(ReducePrecision(knapsack->items[i].value, knapsack->precision)));
}

/**
 * Reducts precision of given number. Ommited precision is set by parameter p.
 *
 * @param   b  bits
 * @param   p  desired precision
 * @return     binary number with reducted precision
 */
bit FPTAS::ReducePrecision(int n, int p) {
    bit b(n);
    return CreateMask(p)&=b;
}

/**
 * Creates binary mask. 'l' rightmost bits have number 1.
 *
 * @param  l  lenght of masked bits
 * @return    binary mask
 */
bit FPTAS::CreateMask(int l) {
    bit mask(0);

    for (int i = 0; i < BITS; ++i)
        if (i >= l) mask.set(i, 1);

    return mask;
}

/**
 * Converts binary number represented by biset to integer representation.
 *
 * @param  b  binary number
 * @return    integer number
 */
int FPTAS::bit2int(bit b) { return (int)(b.to_ulong()); }





// /**
//  * Prints binary vector on standard output.
//  *
//  * @param  bv  binary vector
//  */
// void PrintBinaryVector(std::vector<bool> * bv) {
//     for (auto it = bv->begin(); it != bv->end(); ++it)
//         std::cout << *it;

//     std::cout << std::endl;
// }
// /**
//  * Prints information about cost and weight inside of item.
//  *
//  * @param   item  examined item
//  */
// void PrintItem(Item * item) {
//     std::cout << "(" << item->cost << ", " << item->weight << ")" << std::endl << std::flush;
// }
// /**
//  * Prints all item stored in given column.
//  *
//  * @param   column
//  */
// void  PrintColumn(std::vector<Item *> & column) {
//     for (auto c_it = column.begin(); c_it != column.end(); ++c_it)
//         PrintItem(*c_it);
// }
