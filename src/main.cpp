/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 *
 * @section DESCRIPTION
 *
 * KNAPSACK PROBLEM 
 *
 * Main function.
 */


#include "ExecutionController.h"

int main(int argc, char **argv)
{
    ExecutionController ctrl = ExecutionController(argv[1], argv[3]);
    ctrl.SolveKnapsackProblem((uint8_t)atoi(argv[2]));
}
