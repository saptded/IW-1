//
// Created by saptded on 08.03.2021.
//

#include <stdio.h>
#include "utils.h"
#include <stdlib.h>

#define SIZE 20

void qsortRecursive(int *mas, int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (mas[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (mas[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        qsortRecursive(mas, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        qsortRecursive(&mas[i], size - i);
    }
}

int main() {
    size_t a[3] = {1, 2, 4};
    size_t b[3] = {1, 2, 4};
    // Заполнение массива случайными числами
//    for (size_t i = 0; i < 3; i++)
//        a[i] = rand() % 201 - 100;
//    for (size_t j = 0; j < 3; j++)
//        b[j] = rand() % 201 - 100;

    size_t res = date_comparator(a, b);
    printf("%zu", res);
//    // Вывод элементов массива до сортировки
//    for (int i = 0; i<SIZE; i++)
//        printf("%4d ", a[i]);
//    printf("\n");
//    qsortRecursive(a, SIZE); // вызов функции сортировки
//    // Вывод элементов массива после сортировки
//    for (int i = 0; i<SIZE; i++)
//        printf("%4d ", a[i]);
//    printf("\n");
//    getchar();
//    return 0;
}

//int main() {
//    Tasks *tasks = create_container_for_tasks();
//
//    insert_task(tasks);
//
//    Task task;
//
//    int res = parse_date("10:12:2001", task.date);

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
//}


//printf("----\n");
//for (int j = 0; j < tasks->tasks_amount; ++j) {
//printf("numb: %zu descr: %s\n", tasks->buffer[j].number, tasks->buffer[j].description);
//}
//printf("----\n");