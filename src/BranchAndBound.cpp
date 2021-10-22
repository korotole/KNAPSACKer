#include "BranchAndBound.h"
  
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
    int16_t level, profit, bound;
    uint16_t weight;
};
  
// Comparison function to sort Item according to
// val/weight ratio
bool cmp(Item a, Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}
  
// Returns bound of profit in subtree rooted with u.
// This function mainly uses Greedy solution to find
// an upper bound on maximum profit.
int bound(Node u, uint8_t n, uint16_t M, Item *items)
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
uint16_t BranchAndBound::Knapsack(uint8_t n, uint16_t M, Item *items, TaskType type, int16_t B) {
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

       // if(type == TaskType::desicive && maxProfit >= B) break;
    }
  
    return maxProfit;
}