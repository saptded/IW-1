#include <stdio.h>

#include "utils.h"

int main() {
    Tasks *tasks = create_container_for_tasks();


    while (will_continue_creating_tasks()) {
        if (push_back_task(tasks)) {
            return -1;
        }

    }

    return 0;
}
