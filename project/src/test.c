//
// Created by saptded on 08.03.2021.
//

#include <stdio.h>
#include "utils.h"


int main() {
    Tasks *tasks = create_container_for_tasks();

    int i = 1;
    while(i) {
        insert_task(tasks);
//        i = will_continue_creating_tasks();
        if (tasks->cells_amount == tasks->tasks_amount) {
            if (grow_tasks(tasks)) {
                return -1;
            }
        }

    }
}

