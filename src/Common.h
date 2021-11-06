/**
 * @file
 * @author Oleksandr Korotetskyi <csraea@gmail.com>
 * @date 06/11/2021
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iterator>
#include <bits/stdc++.h>

struct Item {
    uint16_t value;
    uint16_t weight;
};

typedef struct Item Item;

enum class TaskType{
    Exact,
    Constructive,
    Desicive,

    ExactConstructive,
    DesiciveConstructive
};

#endif