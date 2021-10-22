#ifndef EXECUTIONCONTROLLER_H
#define EXECUTIONCONTROLLER_H

#include "Common.h"
#include "BranchAndBound.h"
#include "BruteForce.h"
#include "Dynamic.h"

class ExecutionController {

  private:
    int16_t id = 0, B = 0;
    uint8_t n = 0;
    uint16_t M = 0;
    
    Item *items = 0;
    TaskType type = TaskType::desicive;

  public:
    ExecutionController(const char *type, const char *line) {
        GetKnapsackData(line);
    };

    ~ExecutionController() {
        delete[] items; 
    };

    void SolveKnapsackProblem(uint8_t method);

  private:
    void GetKnapsackData(const char *line); 
    auto GetSolvingFunction(uint8_t method);
    void GetTaskType(const char *type);
};

#endif