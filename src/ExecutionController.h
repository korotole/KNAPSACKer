/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 */

#ifndef EXECUTIONCONTROLLER_H
#define EXECUTIONCONTROLLER_H

#include "Common.h"
#include "BranchBound.h"
#include "BruteForce.h"
#include "Dynamic.h"
#include "GreedyHeruistic.h"
#include "FPTAS.h"
#include "Knapsack.h"

class ExecutionController {

  private:
    
    int32_t method;
    TaskType type;
    Knapsack *knapsack = nullptr;

  public:
    // problem type, knapsack instance
    ExecutionController(int argc, char **argv) {
        GetTaskType(argv[1]);
        GetKnapsackData(argv[4]);
        GetMethod(argv[2]);
        knapsack->SetPrecision(argv[3]);
    };

    ~ExecutionController() {
        delete knapsack; 
    };

    // method of solving
    void SolveKnapsackProblem();

  private:
    void GetKnapsackData(const char *line); 
    auto GetSolvingFunction(int32_t method);
    void GetTaskType(const char *type);
    void GetMethod(const char *method);
    void PrintResults(std::chrono::microseconds duration, uint32_t res);
};

#endif