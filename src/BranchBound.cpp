/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 *
 * @section DESCRIPTION
 *
 * KNAPSACK PROBLEM 
 *
 * Branch & Bound solution.
 */


#include "BranchBound.h"

// Node structure to store information of decision
// tree
struct Node
{
    // level  --> Level of node in decision tree (or index
    //             in arr[]
    // profit --> Profit of nodes on path from root to this
    //            node (including this node)
    // bound ---> Upper bound of maximum profit in subtree
    //            of this node/
    int32_t level, profit, bound;
    uint32_t weight;
};
  
// Comparison function to sort Item according to
// val/weight ratio
inline bool cmp(Item a, Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}
  
// Returns bound of profit in subtree rooted with u.
// This function mainly uses Greedy solution to find
// an upper bound on maximum profit.
inline int bound(Node u, uint8_t n, uint16_t M, Item *items)
{
    // if weight overcomes the knapsack capacity, return
    // 0 as expected bound
    if (u.weight >= M)
        return 0;
  
    // initialize bound on profit by current profit
    int profit_bound = u.profit;
  
    // start including items from index 1 more to current
    // item index
    int j = u.level + 1;
    int totweight = u.weight;
  
    // checking index condition and knapsack capacity
    // condition
    while ((j < n) && (totweight + items[j].weight <= M))
    {
        totweight    += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }
  
    // If k is not n, include last item partially for
    // upper bound on profit
    if (j < n)
        profit_bound += (M - totweight) * items[j].value /
                                         items[j].weight;
  
    return profit_bound;
}
  
// Returns maximum profit we can get with capacity M
uint32_t BranchBound::SolveKnapsack(Knapsack *knapsack, TaskType type) {

    if (type == TaskType::Constructive || type == TaskType::DesiciveConstructive || type == TaskType::ExactConstructive) 
        BranchBound::SolveIBranchBound(knapsack, type);
    
    else {
        Item items[knapsack->n];
        memcpy(items, knapsack->items, sizeof(Item) * knapsack->n);
        knapsack->total = BranchBound::SolveRBranchBound(knapsack->n, knapsack->M, items, type, knapsack->B);
    }

    return knapsack->total;
}


uint32_t BranchBound::SolveRBranchBound(uint8_t n, int32_t M, Item *items, TaskType type, int32_t B) {

    // sorting Item on basis of value per unit weight
    std::sort(items, items + n, cmp);
  
    // make a queue for traversing the node
    std::queue<Node> Q;
    Node u, v;
  
    // dummy node at starting
    u.level = -1;
    u.profit = u.weight = 0;
    Q.push(u);
  
    // One by one extract an item from decision tree
    // compute profit of all children of extracted item
    // and keep saving maxProfit
    int maxProfit = 0;
    while (!Q.empty())
    {
        if(type == TaskType::Desicive && maxProfit >= B) break;

        // Dequeue a node
        u = Q.front();
        Q.pop();
  
        // If it is starting node, assign level 0
        if (u.level == -1)
            v.level = 0;
  
        // If there is nothing on next level
        if (u.level == n-1)
            continue;
  
        // Else if not last node, then increment level,
        // and compute profit of children nodes.
        v.level = u.level + 1;
  
        // Taking current level's item add current
        // level's weight and value to node u's
        // weight and value
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
  
        // If cumulated weight is less than W and
        // profit is greater than previous profit,
        // update maxprofit
        if (v.weight <= M && v.profit > maxProfit)
            maxProfit = v.profit;
  
        // Get the upper bound on profit to decide
        // whether to add v to Q or not.
        v.bound = bound(v, n, M, items);
  
        // If bound value is greater than profit,
        // then only push into queue for further
        // consideration
        if (v.bound > maxProfit)
            Q.push(v);
  
        // Do the same thing,  but Without taking
        // the item in knapsack
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, M, items);
        if (v.bound > maxProfit)
            Q.push(v);
    }
  
    return maxProfit;

}

uint32_t BranchBound::SolveIBranchBound(Knapsack *knapsack, TaskType type) {

    std::vector<bool> solution;

    solution = BranchBound::Evaluate(knapsack, type);
    knapsack->solution = solution;

    return knapsack->total;
}

/**
 * Evaluates particular instances of knapsack problem.
 *
 * @param  inst       instance of knapsack problem
 * @param  capacity   maximum capacity of knapsack
 * @param  max_items  number of allowed items in knapsack
 * @return            solution of particular instances
 */
std::vector<bool> BranchBound::Evaluate(Knapsack *knapsack, TaskType type) {
    // create queue and insert distribution with empty knapsack
    std::queue<std::vector<bool>> queue; 
    queue.push(BranchBound::CreateEmptyKnapsack(knapsack->n));

    // temporary variables
    int8_t tmp_pos;
    std::vector<bool> tmp_item;

    // best solution variables
    uint32_t tmp_best_cost = 0;
    std::vector<bool> tmp_best_distribution;

    // current, remaining cost
    uint32_t cc;
    uint32_t rc;

    // current weight
    uint32_t cw;

    // run till queue is not empty
    while (!queue.empty()) {
        tmp_item = queue.front();
        queue.pop();

        cc = BranchBound::ComputeCurrentCost(&tmp_item, knapsack);

        if (cc >= tmp_best_cost) {
            tmp_best_cost = cc;
            tmp_best_distribution = tmp_item;
        }

        rc = BranchBound::ComputeRemainingCost(&tmp_item, knapsack);

        // COST bounding
        if ((cc + rc) < tmp_best_cost)
            continue;

        cw = BranchBound::ComputeCurrentWeight(&tmp_item, knapsack);

        // find position from where new distributions will be generated
        tmp_pos = BranchBound::GetPosition(&tmp_item);

        for (uint8_t i = tmp_pos+1; i < knapsack->n; ++i) {
            // WEIGHT bounding
            if ((cw + knapsack->items[i].weight) <= knapsack->M)
                queue.push(BranchBound::NextItem(&tmp_item, i));
        }

        if (type == TaskType::DesiciveConstructive && tmp_best_cost >= knapsack->B) break;
        if (type == TaskType::ExactConstructive && tmp_best_cost == knapsack->B) break;

    }

    // stores sum cost of all used items
    knapsack->total = tmp_best_cost;

    return tmp_best_distribution;
}

/**
 * Returns next generated item with defined new position.
 *
 * @param  inst_item  distribution of items in knapsack
 * @param  position   position of new added item
 * @return            new distribution of items in knapsack
 */
std::vector<bool> BranchBound::NextItem(std::vector<bool> * inst_item, uint8_t position) {
    std::vector<bool> tmp_inst = *inst_item;
    tmp_inst.at(position) = 1;

    return tmp_inst;
}

/**
 * Returns index of the last position of number one in vector of bools.
 *
 * @param   inst_item  distribution of items in knapsack
 * @return             position of last binary one
 */
int8_t BranchBound::GetPosition(std::vector<bool> * inst_item) {
    uint8_t tmp_index = 0;
    int8_t index = EMPTY;

    for (auto it = inst_item->begin(); it != inst_item->end(); ++it) {
        if (*it == 1)
            index = tmp_index;

        ++tmp_index;
    }

    return index;
}

/**
 * Creates empty knapsack, binary vector of zeros.
 *
 * @param   size  size of kanpsack
 * @return        generated empty knapsack
 */
std::vector<bool> BranchBound::CreateEmptyKnapsack(uint8_t size) {
    std::vector<bool> knapsack;

    for (int i = 0; i < size; ++i) {
        knapsack.push_back(0);
    }

    return knapsack;
}

/**
 * Compute cost of items added to knapsack.
 *
 * @param   distribution  distribution of items in knapsack
 * @param   inst          holds information about costs and weights of items
 * @return                cost of all items in knapsack
 */
uint32_t BranchBound::ComputeCurrentCost(std::vector<bool> * distribution, Knapsack *knapsack) {
    uint32_t cost = 0;
    uint8_t index = 0;

    for (auto it = distribution->begin(); it != distribution->end(); ++it) {
        if (*it == 1) cost += knapsack->items[index].value;

        ++index;
    }

    return cost;
}

/**
 * Compute cost of items which still can be added to knapsack.
 *
 * @param   distribution  distribution of items in knapsack
 * @param   inst          holds information about costs and weights of items
 * @return                cost of remaining items
 */
uint32_t BranchBound::ComputeRemainingCost(std::vector<bool> * distribution, Knapsack *knapsack) {
    uint32_t cost = 0;
    uint8_t index = 0;
    int8_t offset = BranchBound::GetPosition(distribution) + 1;

    for (auto it = distribution->begin() + offset; it != distribution->end(); ++it) {
            cost += knapsack->items[offset].value;

        ++offset;
    }

    return cost;
}

/**
 * Compute weight of items added to knapsack.
 *
 * @param   distribution  distribution of items in knapsack
 * @param   inst          holds information about costs and weights of items
 * @return                weight of all items in knapsack
 */
uint32_t BranchBound::ComputeCurrentWeight(std::vector<bool> * distribution, Knapsack *knapsack) {
    uint32_t weight = 0;
    uint8_t index = 0;

    for (auto it = distribution->begin(); it != distribution->end(); ++it) {
        if (*it == 1) weight += knapsack->items[index].weight;

        ++index;
    }

    return weight;
}
