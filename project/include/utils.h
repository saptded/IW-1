#ifndef IW_1_PROJECT_INCLUDE_UTILS_H_
#define IW_1_PROJECT_INCLUDE_UTILS_H_

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

typedef struct Task {
    size_t number;
    size_t priority;
    size_t date[3]; // date, month, year(XXXX)
    char *description;
} Task;

typedef struct ArrayOfTasks {
    Task *buffer;
    size_t tasks_amount;
    size_t cells_amount;
} Tasks;

int will_continue_creating_tasks();
int parse_date(const char *date_str, size_t *date_arr);

int read_priority(Task *task);
int read_date(Task *task);
int read_description(Task *task);

int insert_task(Tasks *task);
int grow_tasks(Tasks *tasks);
int push_back_task(Tasks *tasks);
Tasks *create_container_for_tasks();

#endif //IW_1_PROJECT_INCLUDE_UTILS_H_
