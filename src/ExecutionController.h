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
#include "Knapsack.h"

class ExecutionController {

  private:
    
    TaskType type = TaskType::Desicive;
    Knapsack *knapsack = nullptr;

  public:
    // problem type, knapsack instance
    ExecutionController(const char *type, const char *line) {
        GetTaskType(type);
        GetKnapsackData(line);
    };

    ~ExecutionController() {
        delete knapsack; 
    };

    // method of solving
    void SolveKnapsackProblem(uint8_t method);

  private:
    void GetKnapsackData(const char *line); 
    auto GetSolvingFunction(uint8_t method);
    void GetTaskType(const char *type);
    void PrintResults(std::chrono::microseconds duration, uint32_t res);
};

#endif