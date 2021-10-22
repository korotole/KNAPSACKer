#include "BruteForce.h"
 
// Returns the maximum value that
// can be put in a knapsack of capacity M
uint32_t BruteForce::Knapsack(uint8_t n, uint16_t M, Item *items, TaskType type, int32_t B=0){
 
    // Base Case
    if (n == 0 || M == 0 /*|| (B <= 0 && type == TaskType::desicive)*/)   return 0;
 
    // If weight of the nth item is more
    // than Knapsack capacity M, then
    // this item cannot be included
    // in the optimal solution
    if (items[n - 1].weight > M)    return BruteForce::Knapsack(n-1, M, items, type, B);
 
    // Return the maximum of two cases:
    // (1) nth item included
    // (2) not included
    else    
        return std::max( 
                        (uint32_t) (items[n - 1].value + BruteForce::Knapsack(n-1, M - items[n - 1].weight, items, type, B - items[n - 1].weight)),
                        BruteForce::Knapsack(n-1, M, items, type, B)
                    );
}