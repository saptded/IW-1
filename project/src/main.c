#include <stdio.h>

#include "utils.h"

int main() {
    Tasks *tasks = create_container_for_tasks();

    while (will_continue_creating_tasks()) {
        if (push_back_task(tasks)) {
            return -1;
        }

    }

    qsortRecursive(tasks->buffer, tasks->tasks_amount);

    for (size_t k = 0; k < tasks->tasks_amount; k++) {
        printf("priority: %zu number: %zu\n", tasks->buffer[k].priority, tasks->buffer[k].number);
    }


    return 0;
}
