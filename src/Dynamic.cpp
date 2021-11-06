#include "Dynamic.h"
 
// Returns the maximum value that
// can be put in a knapsack of capacity M
uint32_t Dynamic::SolveKnapsack(Knapsack *knapsack, TaskType type) {

    if (type == TaskType::Constructive || type == TaskType::DesiciveConstructive || type == TaskType::ExactConstructive) 
        SolveIDynamic(knapsack, type);
    
    else {
        knapsack->total = SolveRDynamic(knapsack, type);
    }

    return knapsack->total;
}

uint32_t Dynamic::SolveRDynamic(Knapsack *knapsack, TaskType type) {
    int K[knapsack->n + 1][knapsack->M + 1];
 
    // Build table K[][] in bottom up manner
    for (int i = 0; i <= knapsack->n; i++) {
        for (int w = 0; w <= knapsack->M; w++) {

            if (i == 0 || w == 0)                         K[i][w] = 0;
            else if (knapsack->items[i - 1].weight <= w)  K[i][w] = std::max(knapsack->items[i - 1].value + K[i - 1][w - knapsack->items[i - 1].weight], K[i - 1][w]);
            else                                          K[i][w] = K[i - 1][w];
        }
    }
 
    return K[knapsack->n][knapsack->M];
}


/**
 * Evalueates particular instance of knapsack problem by dynamic programming.
 * Firstly the network is created, then solved and solution returned.
 *
 * @param  knapsack   current knapsack interface
 * @return            binary vector, the best selection of items for knapsack
 */
uint32_t Dynamic::SolveIDynamic(Knapsack *knapsack, TaskType type) {

    // create network
    std::vector<std::vector<Cell*>> table = CreateNetwork(knapsack, knapsack->M);

    // compute network values
    SolveNetwork(knapsack, &table, type);

    // deallocate all nodes
    DeleteTable(&table);

    return static_cast<int32_t>(knapsack->total);
}

/**
 * Creates and initializes cell.
 *
 * @param  wi  weight index in knapsack of created cell
 * @return     pointer to new created cell
 */
Cell * Dynamic::CreateCell(int wi) {
    auto cell = new Cell();

    cell->cost = 0;
    cell->weight = 0;
    cell->weight_index = wi;
    cell->forward_first = NULL;
    cell->forward_second = NULL;

    return cell;
}

/**
 * Controls if particular cell does already exist and returns pointer to that cell,
 * otherwise NULL pointer.
 *
 * @param  column  colummn where the search is happening
 * @param  weight  weight of searched cell
 * @return         pointer to searched cell
 */
Cell * Dynamic::ExistCell(std::vector<Cell *> * column, int weight) {
    for (auto it = column->begin(); it != column->end(); ++it)
        if ((*it)->weight_index == weight) return *it;

    return NULL;
}

/**
 * Creates network for compution best combination of items in knapsack.
 * 
 * @param  knapsack  current knapsack interface
 * @param  capacity  capacity of knapsack
 * @return           network used for solving knapsack problem by dynamic programming
 */
std::vector<std::vector<Cell *>> Dynamic::CreateNetwork(Knapsack *knapsack, int32_t capacity) {
    std::vector<Cell*> column;
    int32_t tmp_weight = 0;
    std::vector<std::vector<Cell *>> table;

    Cell *tmp_cell = NULL;

    Cell *init_cell = CreateCell(capacity);
    std::vector<Cell *> init_col = {init_cell};
    table.insert(table.begin(), init_col); 

    for (uint8_t i = 0; i < knapsack->n; i ++) {

        std::vector<Cell*> tmp_column;
        column = table.front();

        for (auto c = column.begin(); c != column.end(); ++c) {
            // first arrow; left direction
            tmp_weight = (*c)->weight_index;

            if ((tmp_cell = ExistCell(&tmp_column, tmp_weight)) == NULL) {
                tmp_cell = CreateCell(tmp_weight);
                tmp_column.push_back(tmp_cell);
            }

            (*c)->forward_first = tmp_cell;

            // second arrow; bottom left direction
            if ( (tmp_weight = (*c)->weight_index - static_cast<int32_t>(knapsack->items[i].weight)) >= 0) {
                if ((tmp_cell = ExistCell(&tmp_column, tmp_weight)) == NULL) {
                    tmp_cell = CreateCell(tmp_weight);
                    tmp_column.push_back(tmp_cell);
                }

                (*c)->forward_second = tmp_cell;
            }

        }

        table.insert(table.begin(), tmp_column); 

    }

    return table;
}

/**
 * Computes weight and cost of selected items in knapsack continuously from zero items 
 * to maximum allowed number of items.
 *
 * @param  knapsack   current knapsack interface
 * @param  table  necessary network used for dynamic programming
 */
void Dynamic::SolveNetwork(Knapsack *knapsack, std::vector<std::vector<Cell *>> *table, TaskType type) {
    Cell *first_cell = nullptr;
    Cell *second_cell = nullptr;
    int tmp_cost_first = 0;
    int tmp_cost_second = 0;
    int tmp_cost_item = 0;

    int cw_it = static_cast<int>(knapsack->n) - 1;

    // solution temporary variables
    Cell * solution_cell = NULL;

    // solves network
    // +1 in iterator is due to starting from second column, 
    // first column is already filled
    for (auto t = table->begin()+1; t != table->end(); ++t, --cw_it) {
        for (auto c = (*t).begin(); c != (*t).end(); ++c) {
            first_cell = (*c)->forward_first;
            second_cell = (*c)->forward_second;

            // just arrow from left direction
            if (second_cell == NULL) {
                (*c)->cost = (*c)->forward_first->cost;
                (*c)->weight += (*c)->forward_first->weight;
                (*c)->direction = 0;
            }
            else {
            // both arrows
                tmp_cost_first = (*c)->forward_first->cost;
                tmp_cost_second = (*c)->forward_second->cost + static_cast<uint32_t>(knapsack->items[cw_it].value);

                // arrow from left direction
                if (tmp_cost_first > tmp_cost_second) {
                    (*c)->cost = tmp_cost_first;
                    (*c)->weight += (*c)->forward_first->weight;
                    (*c)->direction = 0;
                }
                else {
                //arrow from bottom left direction
                    (*c)->cost = tmp_cost_second;
                    (*c)->weight += (*c)->forward_second->weight + static_cast<uint32_t>(knapsack->items[cw_it].weight);
                    (*c)->direction = 1;
                }

                // store temporary best solution
                solution_cell = (*c);
                knapsack->total = static_cast<int32_t>((*c)->cost);

                if (type == TaskType::DesiciveConstructive && knapsack->total >= knapsack->B) break;
                if (type == TaskType::ExactConstructive && knapsack->total == knapsack->B) break;
            }
        }
    }

    knapsack->solution = FindPath(solution_cell);
}

/**
 * Find a path which denotes selected items of knapsack for particular instance. 
 *
 * @param   cell  cell contataining final solution
 * @return        final combination of items in knapsack
 */
std::vector<bool> Dynamic::FindPath(Cell * cell) {
    std::vector<bool> path = { }; // TODO: = path(size, 0), refactor cycle below, might fix the bug with missing zeroes at output
    Cell * tmp_cell = cell;

    while (tmp_cell != NULL) {
        switch (tmp_cell->direction) {
            // left
            case 0:
                path.push_back(0);
                tmp_cell = tmp_cell->forward_first;
                break;

            // bottom left
            case 1:
                path.push_back(1);
                tmp_cell = tmp_cell->forward_second;
                break;
        }
    }

    // delete last item, exceeds limits of knapsack
    // path.erase(path.end());

    return path;
}

/**
 * Deallocate all cells from table.
 *
 * @param  table  pointer to used table/network
 */
void Dynamic::DeleteTable(std::vector<std::vector<Cell*>> * table) {
    for (auto t = table->begin(); t != table->end(); ++t) {
        for (auto c = (*t).begin(); c != (*t).end(); ++c) {
            delete((*c));
        }
    }
}