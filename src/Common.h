#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>

struct Item {
    uint16_t value;
    uint16_t weight;
};

typedef struct Item Item;

enum class TaskType{
    exact,
    constructive,
    desicive
};

#endif