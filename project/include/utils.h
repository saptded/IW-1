#ifndef IW_1_PROJECT_INCLUDE_UTILS_H_
#define IW_1_PROJECT_INCLUDE_UTILS_H_

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

int insert_task(Tasks* task);
int grow_tasks(Tasks *tasks);
int push_back_task(Tasks *tasks);
Tasks *create_container_for_tasks();

#endif //IW_1_PROJECT_INCLUDE_UTILS_H_
