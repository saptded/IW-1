//
// Created by saptded on 08.03.2021.
//

#include <stdio.h>
#include "utils.h"


int main() {
    Tasks *tasks = create_container_for_tasks();

    insert_task(tasks);

    Task task;

    int res = parse_date("10:12:2001", task.date);

//    int i = 1;
//    while(i) {
//        insert_task(tasks);
////        i = will_continue_creating_tasks();
//        if (tasks->cells_amount == tasks->tasks_amount) {
//            if (grow_tasks(tasks)) {
//                return -1;
//            }
//        }
//
//    }
}


//printf("----\n");
//for (int j = 0; j < tasks->tasks_amount; ++j) {
//printf("numb: %zu descr: %s\n", tasks->buffer[j].number, tasks->buffer[j].description);
//}
//printf("----\n");