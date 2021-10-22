#include "ExecutionController.h"

void ExecutionController::GetKnapsackData(const char *line){
    
    FILE *stream = fmemopen ((void*)line, strlen(line), "r");
    if(stream == NULL) {
        perror("fmemopen:\t");
        printf("errno:\t%d\n", errno);

        exit(EXIT_FAILURE);
    }

    fscanf(stream, "%" SCNd16 "%" SCNu8 "%" SCNu16 "%" SCNd32, &(this->id), &(this->n), &(this->M), &(this->B));

    this->items = new Item[this->n] ();    // allocate array of items of desired size

    for(uint8_t i = 0; i < n; i++){
        fscanf(stream, "%" SCNu16 "%" SCNu16, &(this->items[i].weight), &(this->items[i].value));
    }

    fclose(stream);
}


void ExecutionController::GetTaskType(const char *type) {
    if(strcmp(type, "-e") == 0) this->type = TaskType::exact;
    else if(strcmp(type, "-d") == 0) this->type = TaskType::desicive;
    else if(strcmp(type, "-c") == 0) this->type = TaskType::constructive;
    else {
        std::cout << "Error: invalid task type:\t" << type << std::endl;

        exit(EXIT_FAILURE);
    }
}

auto ExecutionController::GetSolvingFunction(uint8_t method){

    switch (method) {
        case 0:     return &BruteForce::Knapsack;
        case 1:     return &BranchAndBound::Knapsack;
        case 2:     return &Dynamic::Knapsack;
        default:    break;
    }

    std::cout << "Default BruteForce method is chosen.\n";
    return &BruteForce::Knapsack;
}

void ExecutionController::SolveKnapsackProblem(uint8_t method) {
    
    auto func = ExecutionController::GetSolvingFunction(method);

    auto start = std::chrono::high_resolution_clock::now();
    auto res = func(this->n, this->M, this->items, this->type, this->B);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << this->id * (-1) << " " << (int) this->n << " " << res << " " << duration.count() << std::endl;
}
