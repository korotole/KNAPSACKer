#include "Dynamic.h"
 
// Returns the maximum value that
// can be put in a knapsack of capacity M
uint32_t Dynamic::Knapsack(uint8_t n, int32_t M, Item *items, TaskType type, int32_t B){

    int K[n + 1][M + 1];
 
    // Build table K[][] in bottom up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= M; w++) {

            if (i == 0 || w == 0)               K[i][w] = 0;
            else if (items[i - 1].weight <= w)  K[i][w] = std::max( items[i - 1].value + K[i - 1][w - items[i - 1].weight], K[i - 1][w]);
            else                                K[i][w] = K[i - 1][w];
        }
    }
 
    return K[n][M];
}