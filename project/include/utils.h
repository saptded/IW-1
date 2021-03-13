#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "utils.h"

#define BUFFER_FOR_DATE_SIZE 4
#define BUFFER_FOR_ANSWER 3
#define COMMON_BUFFER 10
#define SYMBOLS_FOR_DAYS 2
#define SYMBOLS_FOR_MONTHS 2
#define SYMBOLS_OF_YEARS 4
#define BASE 10
#define MAX_DAYS_IN_MONTH 31
#define MAX_MONTHS_IN_YEAR 12
#define CURRENT_YEAR 2021
#define SIZE_OF_DESCRIPTION 100
#define START_SIZE_OF_TASKS_BUFFER 4
#define RHS_IS_LARGER 1
#define LHS_IS_LARGER 2
#define EQUAL 3


typedef struct Task {
    size_t number;
    size_t priority;
    size_t date[3];  // date, month, year(XXXX)
    char *description;
} Task;

typedef struct ArrayOfTasks {
    Task *buffer;
    size_t tasks_amount;
    size_t cells_amount;
} Tasks;

Tasks *create_array_of_tasks();
int print_buffer(const Tasks *tasks);

int will_continue_creating_tasks();

int date_comparator(const size_t *lhs, const size_t *rhs);
int parse_date(const char *date_str, size_t *date_arr);
int tasks_comparator(const Task *lhs, const Task *rhs);

int read_priority(Task *task);
int read_date(Task *task);
int read_description(Task *task);

int push_back_task(Tasks *tasks);
int insert_task(Tasks *task);
int grow_tasks(Tasks *tasks);

int sort(Task *task, size_t size);

#ifdef __cplusplus
};
#endif

#endif  // PROJECT_INCLUDE_UTILS_H_
