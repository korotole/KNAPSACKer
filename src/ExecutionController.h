#ifndef EXECUTIONCONTROLLER_H
#define EXECUTIONCONTROLLER_H

#include "Common.h"
#include "BranchAndBound.h"
#include "BruteForce.h"
#include "Dynamic.h"

class ExecutionController {

  private:
    int16_t id = 0; 
    int32_t B = 0;  // požadovana minimální cena
    uint8_t n = 0;  // počet věcí
    uint16_t M = 0; // kapacita batohu
    
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