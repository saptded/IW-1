#include <gtest/gtest.h>
#include <cstring>

#include "utils.h"

#define ERR -1

TEST(data_compatator, data_comparator0) {
    size_t *a = nullptr;
    size_t *b = nullptr;

    EXPECT_EQ(ERR, date_comparator(a, b));
}

TEST(data_compatator, data_comparator1) {
    int equal = EQUAL;

    size_t a[3] = {10, 10, 2010};
    size_t b[3] = {10, 10, 2010};

    EXPECT_EQ(equal, date_comparator(a, b));
}

TEST(data_compatator, data_comparator2) {
    size_t a0[3] = {10, 10, 2010};
    size_t b0[3] = {10, 10, 2011};
    size_t a1[3] = {10, 9, 2010};
    size_t b1[3] = {10, 10, 2010};
    size_t a2[3] = {9, 10, 2010};
    size_t b2[3] = {10, 10, 2010};

    EXPECT_EQ(RHS_IS_LARGER, date_comparator(a0, b0));
    EXPECT_EQ(RHS_IS_LARGER, date_comparator(a1, b1));
    EXPECT_EQ(RHS_IS_LARGER, date_comparator(a2, b2));
}

TEST(data_compatator, data_comparator3) {
    int lhs_is_larger = LHS_IS_LARGER;

    size_t a3[3] = {10, 10, 2011};
    size_t b3[3] = {10, 10, 2010};
    size_t a4[3] = {10, 10, 2010};
    size_t b4[3] = {10, 9, 2010};
    size_t a5[3] = {10, 10, 2010};
    size_t b5[3] = {9, 10, 2010};

    EXPECT_EQ(lhs_is_larger, date_comparator(a3, b3));
    EXPECT_EQ(lhs_is_larger, date_comparator(a4, b4));
    EXPECT_EQ(lhs_is_larger, date_comparator(a5, b5));
}

TEST(date_parse, date_parse0) {
    char *date0 = nullptr;
    std::string date1 = "10:10:2022";
    std::string date2 = "10:13:2020";
    std::string date3 = "33:09:2010";

    size_t *a0 = nullptr;
    size_t a1[3] = {0, 0, 0};

    EXPECT_EQ(ERR, parse_date(date0, a0));
    EXPECT_EQ(ERR, parse_date(date1.c_str(), a1));
    EXPECT_EQ(ERR, parse_date(date1.c_str(), a1));
    EXPECT_EQ(ERR, parse_date(date2.c_str(), a1));
    EXPECT_EQ(ERR, parse_date(date3.c_str(), a1));
}

TEST(date_parse, date_parse1) {
    std::string date1 = "10:10:2021";

    size_t a0[3];
    size_t a1[3] = {10, 10, 2021};

    parse_date(date1.c_str(), &a0[0]);

    EXPECT_TRUE(0 == std::memcmp(a0, a1, sizeof(a0)));
}

TEST(tasks_comparator, tasks_comparator0) {
    Task task1 = {1, 1, {10, 10, 21}, nullptr};
    Task task2 = {1, 1, {10, 10, 20}, nullptr};

    Task task3 = {1, 1, {10, 10, 20}, nullptr};
    Task task4 = {1, 2, {10, 10, 20}, nullptr};


    int res1 = tasks_comparator(&task1, &task2);
    int res2 = tasks_comparator(&task3, &task4);

    EXPECT_EQ(LHS_IS_LARGER, res1);
    EXPECT_EQ(RHS_IS_LARGER, res2);
}

TEST(sort, sort) {
    Task task1 = {1, 1, {10, 10, 2020}, nullptr};
    Task task2 = {2, 1, {1, 10, 2020}, nullptr};
    Task task3 = {3, 3, {10, 9, 2020}, nullptr};
    Task task4 = {4, 2, {1, 10, 1817}, nullptr};
    Task task5 = {5, 10, {10, 10, 2001}, nullptr};

    Task tasks0[5] = {task1, task2, task3, task4, task5};
    Task tasks1[5] = {task2, task1, task4, task3, task5};

    sort(tasks0, 5);

    EXPECT_TRUE(0 == std::memcmp(tasks0, tasks1, sizeof(tasks0)));
}

TEST(grow_buffer, grow_buffer) {
    Tasks *tasks = create_array_of_tasks();

    EXPECT_EQ(0, grow_tasks(tasks));

    EXPECT_EQ(START_SIZE_OF_TASKS_BUFFER * 2, tasks->cells_amount);
    free(tasks->buffer);
    free(tasks);
}

TEST(push_back_task, push_back_task) {
    Tasks *tasks = create_array_of_tasks();
    size_t a[3] = {1, 2, 3};

    Task *task = (Task *) calloc(1, sizeof(Task));
    task->number = 1;
    task->priority = 1;
    for (size_t i = 0; i < 3; ++i) {
        task->date[i] = i + 1;
    }

    EXPECT_EQ(0, push_back_task(tasks, task));

    EXPECT_EQ(1, tasks->tasks_amount);
    EXPECT_EQ(1, tasks->buffer->number);
    EXPECT_EQ(1, tasks->buffer->priority);
    EXPECT_TRUE(0 == std::memcmp(a, tasks->buffer->date, sizeof(a)));
    EXPECT_EQ(nullptr, tasks->buffer->description);

    free(tasks);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}