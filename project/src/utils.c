#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "utils.h"

int print_buffer(const Tasks *tasks) {
    if (tasks == NULL || tasks->tasks_amount == 0) {
        return -1;
    }

    for (size_t k = 0; k < tasks->tasks_amount; k++) {
        printf("priority: %zu number: %zu\n", tasks->buffer[k].priority, tasks->buffer[k].number);
        for (size_t i = 0; i < 3; ++i) {
            printf("%zu ", tasks->buffer[k].date[i]);
        }
        printf("\n");
        printf("%s\n----\n", tasks->buffer[k].description);
    }

    return 0;
}

int date_comparator(const size_t *lhs, const size_t *rhs) {
    if (lhs == NULL || rhs == NULL) {
        return -1;
    }

    for (int i = 2; i >= 0; --i) {
        if (!i) {
            break;
        }
        if (lhs[i] > rhs[i]) {
            return LHS_IS_LARGER;
        } else if (lhs[i] < rhs[i]) {
            return RHS_IS_LARGER;
        }
    }

    return EQUAL;
}

int tasks_comparator(const Task *lhs, const Task *rhs) {
    if (lhs == NULL || rhs == NULL) {
        return -1;
    }

    if (lhs->priority > rhs->priority) {
        return LHS_IS_LARGER;
    } else if (lhs->priority < rhs->priority) {
        return RHS_IS_LARGER;
    }
    if (date_comparator(lhs->date, rhs->date) == LHS_IS_LARGER) {
        return LHS_IS_LARGER;
    } else if (date_comparator(lhs->date, rhs->date) == RHS_IS_LARGER) {
        return RHS_IS_LARGER;
    }

    return EQUAL;
}

int sort(Task *task, const size_t size) {
    if (task == NULL || task->number == 0) {
        return -1;
    }

    size_t i = 0;
    size_t j = size - 1;
    Task mid = task[size / 2];

    while (i <= j) {
        while (tasks_comparator(&task[i], &mid) == RHS_IS_LARGER) {
            i++;
        }

        while (tasks_comparator(&task[j], &mid) == LHS_IS_LARGER) {
            j--;
        }

        if (j == 0 && i == 0) {
            return 0;
        }

        if (i <= j) {
            Task tmp = task[i];
            task[i] = task[j];
            task[j] = tmp;

            i++;
            j--;
        }
    }

    if (j > 0) {
        sort(task, j + 1);
    }
    if (i < size) {
        sort(&task[i], size - i);
    }

    return 0;
}

int parse_date(const char *date_str, size_t *date_arr) {
    if (date_arr == NULL) {
        return -1;
    }

    int i = 0;
    char *end = NULL;
    char *buf = (char *) calloc(BUFFER_FOR_DATE_SIZE, sizeof(char));

    while (*(date_str + i) != ':' && i != SYMBOLS_FOR_DAYS) {
        buf[i] = date_str[i];
        i++;
    }
    date_arr[0] = (size_t) strtol(buf, &end, BASE);
    if (*end != '\0' || date_arr[0] > MAX_DAYS_IN_MONTH) {
        free(buf);
        return -1;
    }

    date_str += (i + 1);
    i = 0;

    while (*(date_str + i) != ':' && i != SYMBOLS_FOR_MONTHS) {
        buf[i] = date_str[i];
        i++;
    }
    date_arr[1] = (size_t) strtol(buf, &end, BASE);
    if (*end != '\0' || date_arr[1] > MAX_MONTHS_IN_YEAR) {
        free(buf);
        return -1;
    }

    date_str += (i + 1);
    i = 0;

    while (*(date_str + i) != '\0' && i != SYMBOLS_OF_YEARS) {
        buf[i] = date_str[i];
        i++;
    }
    date_arr[2] = (size_t) strtol(buf, &end, BASE);
    if (*end != '\0' || date_arr[2] > CURRENT_YEAR) {
        free(buf);
        return -1;
    }

    free(buf);
    return 0;
}

int will_continue_creating_tasks() {
    printf("Do you want to create a task(y or n): ");

    char ans[BUFFER_FOR_ANSWER];
    int res = scanf("%2s", ans);
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
    char *buf = (char *) calloc(COMMON_BUFFER, sizeof(char));
    if (buf == NULL) {
        return -1;
    }
    if (scanf("%10s", buf) != 1) {
        free(buf);
        return -1;
    }
    task->priority = (size_t) strtol(buf, &end, BASE);
    if (*end != '\0') {
        free(buf);
        return -1;
    }

    free(buf);
    return 0;
}

int read_date(Task *task) {
    if (task == NULL) {
        return -1;
    }
    printf("date(XX:XX:XXXX): ");

    char *date_buf = (char *) calloc(COMMON_BUFFER, sizeof(char));
    if (date_buf == NULL) {
        free(date_buf);
        return -1;
    }
    if (scanf("%10s", date_buf) != 1) {
        free(date_buf);
        return -1;
    }
    if (parse_date(date_buf, task->date) == -1) {
        free(date_buf);
        return -1;
    }

    free(date_buf);
    return 0;
}

int read_description(Task *task) {
    if (task == NULL) {
        return -1;
    }
    printf("description: ");

    task->description = (char *) calloc(SIZE_OF_DESCRIPTION, sizeof(char));
    if (task->description == NULL) {
        return -1;
    }
    if (scanf("%100s", task->description) != 1) {
        return -1;
    }

    return 0;
}

Tasks *create_array_of_tasks() {
    Tasks *tasks = (Tasks *) calloc(1, sizeof(Tasks));
    if (tasks == NULL) {
        return NULL;
    }

    tasks->buffer = (Task *) calloc(START_SIZE_OF_TASKS_BUFFER, sizeof(Task));
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
