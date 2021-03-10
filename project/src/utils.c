#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "utils.h"

int parse_date(const char *date_str, size_t *date_arr) {
    if (date_arr == NULL) {
        return -1;
    }

    int i = 0;
    char *end = NULL;
    char *buf = (char*) calloc(4, sizeof(char));

    while(*(date_str + i) != ':' && i != 2) {
        buf[i] = date_str[i];
        i++;
    }
    date_arr[0] = (size_t) strtol(buf, &end, 10);
    if (*end != '\0' || date_arr[0] <= 0 || date_arr[0] > 31) {
        return -1;
    }

    date_str += (i + 1);
    i = 0;

    while(*(date_str + i) != ':' && i != 2) {
        buf[i] = date_str[i];
        i++;
    }
    date_arr[1] = (size_t) strtol(buf, &end, 10);
    if (*end != '\0' || date_arr[1] <= 0 || date_arr[1] > 12) {
        return -1;
    }

    date_str += (i + 1);
    i = 0;

    while(*(date_str + i) != '\0' && i != 4) {
        buf[i] = date_str[i];
        i++;
    }
    date_arr[2] = (size_t) strtol(buf, &end, 10);
    if (*end != '\0' || date_arr[2] <= 0 || date_arr[2] > 2021) {
        return -1;
    }

    free(buf);
    return 0;

}

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

    if (read_priority(&task) == -1) {
        return -1;
    }
    if (read_date(&task) == -1) {
        return -1;
    }
    if (read_description(&task) == -1) {
        return -1;
    }

    *(tasks->buffer + tasks->tasks_amount) = task;
    tasks->tasks_amount++;

    return 0;
}

int read_priority(Task *task) {
    if (task == NULL) {
        return -1;
    }
    printf("number: %zu\npriority: ", task->number);

    char *end = NULL;
    char *buf = (char *) calloc(10, sizeof(char));
    if (buf == NULL) {
        return -1;
    }
    if (scanf("%10s", buf) != 1) {
        return -1;
    }
    task->priority = (size_t) strtol(buf, &end, 10);
    if (*end != '\0') {
        return -1;
    }

    return 0;
}

int read_date(Task *task) {
    if (task == NULL) {
        return -1;
    }
    printf("date(XX:XX:XXXX): ");

    char *date = (char *) calloc(10, sizeof(char));
    if (date == NULL) {
        return -1;
    }
    if (scanf("%10s", date) != 1) {
        return -1;
    }
    if (parse_date(date, task->date) == -1) {
        return -1;
    }

    free(date);
    return 0;
}

int read_description(Task *task) {
    if (task == NULL) {
        return -1;
    }
    printf("description: ");

    task->description = (char *) calloc(100, sizeof(char));
    if (task->description == NULL) {
        return -1;
    }
    if (scanf("%100s", task->description) != 1) {
        return -1;
    }

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
    if (tmp_buffer == NULL) {
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

    if (insert_task(tasks)) {
        return -1;
    }

    return 0;
}
