#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "utils.h"

int qsortRecursive(Task *task, const size_t size) {

    //Указатели в начало и в конец массива
    size_t i = 0;
    size_t j = size - 1;

    //Центральный элемент массива
    size_t mid = task[size / 2].priority;

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while(task[i].priority < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while(task[j].priority > mid) {
            j--;
        }

        if (j == 0 && i == 0) {
            return 0;
        }

        //Меняем элементы местами
        if (i <= j) {
            Task tmp = task[i];
            task[i] = task[j];
            task[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > 0) {
        //"Левый кусок"
        qsortRecursive(task, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        qsortRecursive(&task[i], size - i);
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
    if (*end != '\0' || date_arr[0] <= 0 || date_arr[0] > MAX_DAYS_IN_MONTH) {
        return -1;
    }

    date_str += (i + 1);
    i = 0;

    while (*(date_str + i) != ':' && i != SYMBOLS_FOR_MONTHS) {
        buf[i] = date_str[i];
        i++;
    }
    date_arr[1] = (size_t) strtol(buf, &end, BASE);
    if (*end != '\0' || date_arr[1] <= 0 || date_arr[1] > MAX_MONTHS_IN_YEAR) {
        return -1;
    }

    date_str += (i + 1);
    i = 0;

    while (*(date_str + i) != '\0' && i != SYMBOLS_OF_YEARS) {
        buf[i] = date_str[i];
        i++;
    }
    date_arr[2] = (size_t) strtol(buf, &end, BASE);
    if (*end != '\0' || date_arr[2] <= 0 || date_arr[2] > CURRENT_YEAR) {
        return -1;
    }

    free(buf);
    return 0;

}

int will_continue_creating_tasks() {
    printf("Do you want to create a task(y or n): ");

    char ans[BUFFER_FOR_ANSWER];
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
    char *buf = (char *) calloc(COMMON_BUFFER, sizeof(char));
    if (buf == NULL) {
        return -1;
    }
    if (scanf("%10s", buf) != 1) {
        return -1;
    }
    task->priority = (size_t) strtol(buf, &end, BASE);
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

    char *date_buf = (char *) calloc(COMMON_BUFFER, sizeof(char));
    if (date_buf == NULL) {
        return -1;
    }
    if (scanf("%10s", date_buf) != 1) {
        return -1;
    }
    if (parse_date(date_buf, task->date) == -1) {
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

Tasks *create_container_for_tasks() {
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
