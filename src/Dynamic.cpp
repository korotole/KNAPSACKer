#include "Dynamic.h"
 
// Returns the maximum value that
// can be put in a knapsack of capacity M
uint16_t Dynamic::Knapsack(uint8_t n, uint16_t M, Item *items, TaskType type, int16_t B){
    int i, w;
    // int K[n + 1][W + 1];
 
    // // Build table K[][] in bottom up manner
    // for (i = 0; i <= n; i++)
    // {
    //     for (w = 0; w <= W; w++)
    //     {
    //         if (i == 0 || w == 0)
    //             K[i][w] = 0;
    //         else if (wt[i - 1] <= w)
    //             K[i][w] = std::max( val[i - 1] + K[i - 1][w - wt[i - 1]],
    //                                 K[i - 1][w]);
    //         else
    //             K[i][w] = K[i - 1][w];
    //     }
    // }
 
    return 0;
    // return K[n][W];
}