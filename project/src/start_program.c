#include <stdio.h>

#include "start_program.h"
#include "utils.h"

int start_program() {
    Tasks *tasks = create_array_of_tasks();
    if (tasks == NULL) {
        return -1;
    }

    while (will_continue_creating_tasks()) {
        if (push_back_task(tasks)) {
            return -1;
        }

    }

    if (sort(tasks->buffer, tasks->tasks_amount) == -1) {
        return -1;
    }

    if (print_buffer(tasks) == -1) {
        return -1;
    }

    return 0;
}
