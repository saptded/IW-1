//
// Created by saptded on 08.03.2021.
//

#include <stdio.h>
#include "utils.h"

int main() {
    Task task;

    while(task.number != -1) {
        scanf("%zu %zu %s %s", &task.number, &task.priority, task.date, task.description);
        printf("%zu %zu %s %s", task.number, task.priority, task.date, task.description);
    }
}

