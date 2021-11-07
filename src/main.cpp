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
    ExecutionController ctrl = ExecutionController(argc, argv);
    ctrl.SolveKnapsackProblem();
}
