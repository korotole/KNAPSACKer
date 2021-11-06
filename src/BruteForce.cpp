/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 *
 * @section DESCRIPTION
 *
 * KNAPSACK PROBLEM 
 *
 * Brute Force solution.
 */


#include "BruteForce.h"
 
// Returns the maximum value that
// can be put in a knapsack of capacity M
uint32_t BruteForce::SolveKnapsack(Knapsack *knapsack, TaskType type){
    
    if (type == TaskType::Constructive || type == TaskType::DesiciveConstructive || type == TaskType::ExactConstructive) 
        BruteForce::SolveIBruteForce(knapsack, type);
    
    else
        knapsack->total = BruteForce::SolveRBruteForce(knapsack->n, knapsack->M, knapsack->items, type, knapsack->B);
    
    return knapsack->total;
}

uint32_t BruteForce::SolveRBruteForce(uint8_t n, int32_t M, Item *items, TaskType type, int32_t B){
 
    // Base Case
    if (n == 0 || M <= 0 || (B <= 0 && type == TaskType::Desicive))   return 0;
 
    // If weight of the nth item is more
    // than Knapsack capacity M, then
    // this item cannot be included
    // in the optimal solution
    if (items[n - 1].weight > M)    return BruteForce::SolveRBruteForce(n-1, M, items, type, B);
 
    // Return the maximum of two cases:
    // (1) nth item included
    // (2) not included
    else return std::max( 
                        (uint32_t) (items[n - 1].value + BruteForce::SolveRBruteForce(n-1, M - items[n - 1].weight, items, type, B - items[n - 1].value)),
                        BruteForce::SolveRBruteForce(n-1, M, items, type, B)
                    );
}


void BruteForce::SolveIBruteForce(Knapsack *knapsack, TaskType type) {
    
    std::vector<std::vector<bool>> * combinations = BruteForce::GenerateCombinations(knapsack->n, knapsack->n);
    std::vector<bool> solution;

    solution = BruteForce::Evaluate(knapsack, type, combinations);

    knapsack->solution = solution;

    delete combinations;
}

/**
 * Generate all possible combinations.
 *
 * @param len       length of vector
 * @param max_item  maximum number of 1's
 * @return          all_combinations
 */
std::vector<std::vector<bool>> * BruteForce::GenerateCombinations(int len, int max_item) {
    auto combinations = new std::vector<std::vector<bool>>;

    for (int i = 1; i <= max_item; ++i) {
        std::vector<bool> v(len);
        std::fill(v.begin() + len - i, v.end(), true);

        do {
            combinations->push_back(v);
        } while (std::next_permutation(v.begin(), v.end()));
    }

    return combinations;
}


std::vector<bool> BruteForce::Evaluate(Knapsack *knapsack, TaskType type, std::vector<std::vector<bool>> *comb) {
    std::vector<bool> solution;
    int min_cost = 0;
    Item ev;

    for (auto comb_it = comb->begin() ; comb_it != comb->end(); ++comb_it) {
        ev = BruteForce::EvaluateCombination(knapsack, type, &(*comb_it));

        if (ev.weight <= knapsack->M) 
           if (ev.value >= min_cost) {
               solution = *comb_it;
               min_cost = ev.value;
           }

        if (type == TaskType::DesiciveConstructive && min_cost >= knapsack->B) break;
        if (type == TaskType::ExactConstructive && min_cost == knapsack->B) break;
    }

    // // stores sum of all weight
    knapsack->total = min_cost;

    return solution;
}

Item BruteForce::EvaluateCombination(Knapsack *knapsack, TaskType type, std::vector<bool> * comb) {
    Item ev;
    ev.value = 0;
    ev.weight = 0;

    auto comb_it = comb->begin();
    for (uint8_t i = 0; i < knapsack->n; i++, ++comb_it) {
        if (*comb_it == true) {
           ev.value += knapsack->items[i].value; 
           ev.weight += knapsack->items[i].weight; 
        }
    }

    return ev;
}