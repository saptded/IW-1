#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "utils.h"

int will_continue_creating_tasks() {
    printf("Do you want to create a task(y or n): ");

    char ans[3];
    int res = scanf("%3s", ans);
    if (res != 1) {
        return -1;
    }

    if (*ans == 'y') {
        return 1;
    }

    return 0;
}

int insert_task(Tasks *tasks) {
    if (tasks == NULL) {
        return -1;
    }

    Task task;
    task.number = tasks->tasks_amount + 1;
    task.date = (char *) calloc(10, sizeof(char));
    if (task.date == NULL) {
        return -1;
    }
    task.description = (char *) calloc(100, sizeof(char));
    if (task.description == NULL) {
        return -1;
    }

    printf("number: %zu\npriority: ", task.number);
    if (scanf("%zu", &task.priority) != 1) {
        return -1;
    }
    printf("date: ");
    if (scanf("%9s", task.date) != 1) {
        return -1;
    }
    printf("description: ");
    if (scanf("%99s", task.description) != 1) {
        return -1;
    }

    *(tasks->buffer + tasks->tasks_amount) = task;
    tasks->tasks_amount++;

    printf("----\n");
    for (int j = 0; j < tasks->tasks_amount; ++j) {
        printf("numb: %zu descr: %s\n", tasks->buffer[j].number, tasks->buffer[j].description);
    }
    printf("----\n");

    return 0;
}

Tasks *create_container_for_tasks() {
    Tasks *tasks = (Tasks *) calloc(1, sizeof(Tasks));
    if (tasks == NULL) {
        return NULL;
    }

    tasks->buffer = (Task *) calloc(1, sizeof(Task));
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
    Task *tmp_buffer = (Task *) calloc(tasks->cells_amount, sizeof(Task));
    if (tmp_buffer == NULL) {
        return -1;
    }

    tmp_buffer = memcpy(tmp_buffer, tasks->buffer, tasks->tasks_amount * sizeof(Task));
    if(tmp_buffer == NULL) {
        return -1;
    }

    tasks->buffer = tmp_buffer;

    return 0;
}

int push_back_task(Tasks *tasks) {
    if (tasks == NULL) {
        return -1;
    }

    if (tasks->cells_amount == tasks->tasks_amount) {
        if (grow_tasks(tasks)) {
            return -1;
        }
    }

    if(insert_task(tasks)) {
        return -1;
    }

    return 0;
}
