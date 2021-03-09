#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

int insert_task(Tasks *tasks) {
    if (tasks == NULL) {
        return -1;
    }

    size_t len = BUFFER_STR;
    int res = 0;

    Task task;
    task.number = tasks->tasks_amount + 1;
    printf("priority: ");
    res = scanf("%zu", &task.priority);
    if (res != 1) {
        return 1;
    }
    printf("date: ");
    res = scanf("%s", task.date);
    printf("description: ");
    res = scanf("%s", task.description);


//    int res = scanf("%zu %zu %s %s", &task.number, &task.priority, task.date, task.description);
//
//    if (res == 0) {
//        return 1;
//    } else if (res != 4) {
//        return -1;
//    }

    *(tasks->buffer + tasks->tasks_amount) = task;
    tasks->tasks_amount++;

    return 0;
}

Tasks *create_container_for_tasks() {
    Tasks *tasks = (Tasks *) calloc(1, sizeof(Tasks));
    if (tasks == NULL) {
        return NULL;
    }

    tasks->buffer = (Task *) calloc(4, sizeof(Task));
    if (tasks->buffer == NULL) {
        free(tasks);
        return NULL;
    }

    tasks->tasks_amount = 0;
    tasks->cells_amount = 1;

    return tasks;
}

int grow_tasks(Tasks *tasks) {
    if (tasks == NULL) {
        return -1;
    }

    tasks->cells_amount *= 2;
    tasks->buffer = (Task *) realloc(tasks->buffer, tasks->cells_amount);
    if (tasks->buffer == NULL) {
        return -1;
    }

    return 0;
}

int add_task(Tasks *tasks) {
    if (tasks == NULL) {
        return -1;
    }

    if (tasks->cells_amount == tasks->tasks_amount) {
        if (grow_tasks(tasks)) {
            return -1;
        }
    }

    int res = insert_task(tasks);
    if (res == -1) {
        return -1;
    } else if (res == 1) {
        return 1;
    }

    return 0;
}
