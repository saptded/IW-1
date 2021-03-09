#include <stdio.h>

#include "utils.h"

int main() {
    Tasks *tasks = create_container_for_tasks();

    int res = 0;
    while(res != 1) {
        res = add_task(tasks);

        for (int i = 0; i < tasks->tasks_amount; i++) {
            printf("%zu ", tasks->buffer[i].number);
        }

        printf("_____\n");
    }

    return 0;
}
