/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 *
 * @section DESCRIPTION
 *
 * KNAPSACK PROBLEM 
 *
 * Program execution controller.
 */


#include "ExecutionController.h"

void ExecutionController::GetKnapsackData(const char *line){
    
    int16_t id = 0; 
    int32_t B = 0;  // požadovana minimální cena
    uint8_t n = 0;  // počet věcí
    int32_t M = 0;  // kapacita batohu

    FILE *stream = fmemopen ((void*)line, strlen(line), "r");
    if(stream == NULL) {
        perror("fmemopen:\t");
        printf("errno:\t%d\n", errno);

        exit(EXIT_FAILURE);
    }


    if ( this->type == TaskType::DesiciveConstructive || this->type == TaskType::Desicive || this->type == TaskType::Exact || this->type == TaskType::ExactConstructive )
        fscanf(stream, "%" SCNd16 "%" SCNu8 "%" SCNd32 "%" SCNd32, &id, &n, &M, &B);

    else    //TODO modify according to new file format
        fscanf(stream, "%" SCNd16 "%" SCNu8 "%" SCNd32, &id, &n, &M);


    this->knapsack = new Knapsack(id, B, n, M);

    for(uint8_t i = 0; i < n; i++){
        fscanf(stream, "%" SCNu16 "%" SCNu16, &(this->knapsack->items[i].weight), &(this->knapsack->items[i].value));
    }

    fclose(stream);
}


void ExecutionController::GetTaskType(const char *type) {
    if(strcmp(type, "-e") == 0) this->type = TaskType::Exact;
    else if(strcmp(type, "-d") == 0) this->type = TaskType::Desicive;
    else if(strcmp(type, "-c") == 0) this->type = TaskType::Constructive;
    else if(strcmp(type, "-dc") == 0) this->type = TaskType::DesiciveConstructive;
    else if(strcmp(type, "-ec") == 0) this->type = TaskType::ExactConstructive;
    else if(strcmp(type, "-cd") == 0) this->type = TaskType::DesiciveConstructive;
    else if(strcmp(type, "-ce") == 0) this->type = TaskType::ExactConstructive;
    else {
        std::cout << "Error: invalid task type:\t" << type << std::endl;

        exit(EXIT_FAILURE);
    }
}

auto ExecutionController::GetSolvingFunction(int32_t method){

    switch (method) {
        case 0:     return &BruteForce::SolveKnapsack;
        case 1:     return &BranchBound::SolveKnapsack;
        case 2:     return &Dynamic::SolveKnapsack;
        case 3:     return &GreedyHeruistic::SolveKnapsack;
        case 4:     return &FPTAS::SolveKnapsack;
        default:    break;
    }

    std::cout << "Default BruteForce method is chosen.\n";
    return &BruteForce::SolveKnapsack;
}

void ExecutionController::SolveKnapsackProblem() {
    
    auto func = GetSolvingFunction(this->method);

    auto start = std::chrono::high_resolution_clock::now();
    auto res = func(this->knapsack, this->type);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    PrintResults(duration, res);
}

void ExecutionController::PrintResults(std::chrono::microseconds duration, uint32_t res) {
    // printing results below

    std::cout << static_cast<int>(this->knapsack->id) * (-1) << " " <<  static_cast<int>(this->knapsack->n) << " " << static_cast<int>(res) << " " << duration.count();

    if (this->type == TaskType::Constructive || this->type == TaskType::DesiciveConstructive || this->type == TaskType::ExactConstructive){
        std::cout << " ";
        if(!this->knapsack->solution.empty()) {
            // solve strange printing bug 
            auto lim =  (int)knapsack->n - this->knapsack->solution.size() + 1;
            for(uint8_t i = 0; i < lim; i++) {
                std::cout << "0";
            }
            
            for (auto it = this->knapsack->solution.begin(); it != knapsack->solution.end() -1; it++) {
                std::cout << "" << *(it);
            }

        } else {
            
            for (uint8_t i = 0; i < knapsack->n; i++) {
                std::cout << "0";
            }

        }
        
    }

    std::cout << std::endl;
}

void ExecutionController::GetMethod(const char *m) {
    this->method = atoi(m);
}