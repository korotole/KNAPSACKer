#include "ExecutionController.h"

int main(int argc, char **argv) {

    ExecutionController ctrl = ExecutionController(argv[1], argv[3]);
    ctrl.SolveKnapsackProblem((uint8_t)atoi(argv[2]));

}

