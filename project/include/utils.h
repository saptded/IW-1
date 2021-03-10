#ifndef IW_1_PROJECT_INCLUDE_UTILS_H_
#define IW_1_PROJECT_INCLUDE_UTILS_H_

#define DATE_SIZE 10
#define DESCRIPTION_SIZE 100

typedef struct Task {
    size_t number;
    size_t priority;
    char *date;
    char *description;
} Task;

typedef struct ArrayOfTasks {
    Task *buffer;
    size_t tasks_amount;
    size_t cells_amount;
} Tasks;

int will_continue_creating_tasks();

int insert_task(Tasks* task);
int grow_tasks(Tasks *tasks);
int push_back_task(Tasks *tasks);
Tasks *create_container_for_tasks();

#endif //IW_1_PROJECT_INCLUDE_UTILS_H_
