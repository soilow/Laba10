#include <lib/Scheduler.h>
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

TEST(SchedulerTestSuite, DefaultTest) {
    float a = 1;
    float b = -2;
    float c = 0;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](float a, float c){return -4 * a * c;}, a, c);

    auto id2 = scheduler.Add([](float b, float v){return b * b + v;}, b, scheduler.GetFutureResult<float>(id1));

    auto id3 = scheduler.Add([](float b, float d){return -b + std::sqrt(d);}, b, scheduler.GetFutureResult<float>(id2));

    auto id4 = scheduler.Add([](float b, float d){return -b - std::sqrt(d);}, b, scheduler.GetFutureResult<float>(id2));

    auto id5 = scheduler.Add([](float a, float v){return v/(2*a);}, a, scheduler.GetFutureResult<float>(id3));

    auto id6 = scheduler.Add([](float a, float v){return v/(2*a);},a, scheduler.GetFutureResult<float>(id4));

    scheduler.ExecuteAll();

    EXPECT_EQ(scheduler.GetResult<float>(id5), 2);
    EXPECT_EQ(scheduler.GetResult<float>(id6), 0);
}

TEST(SchedulerTestSuite, FutureResultTest1) {
    int a = 5;
    int b = 10;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](int a, int b) { return a + b; }, a, b);
    auto id2 = scheduler.Add([](int a, int b) { return a * b; }, a, scheduler.GetFutureResult<int>(id1));

    scheduler.ExecuteAll();

    EXPECT_EQ(scheduler.GetResult<int>(id1), 15);
    EXPECT_EQ(scheduler.GetResult<int>(id2), 75);
}

TEST(SchedulerTestSuite, FutureResultTest2) {
    int x = 8;
    int y = 3;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](int x, int y) { return x / y; }, x, y);
    auto id2 = scheduler.Add([](int x, int y) { return x * y; }, x, scheduler.GetFutureResult<int>(id1));

    scheduler.ExecuteAll();

    EXPECT_EQ(scheduler.GetResult<int>(id1), 2);
    EXPECT_EQ(scheduler.GetResult<int>(id2), 16);
}

TEST(SchedulerTestSuite, FutureResultTest3) {
    float p = 3.14;
    float q = 2.5;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](float p, float q) { return p * q; }, p, q);
    auto id2 = scheduler.Add([](float p, float q) { return q / p; }, p, scheduler.GetFutureResult<float>(id1));

    scheduler.ExecuteAll();

    EXPECT_FLOAT_EQ(scheduler.GetResult<float>(id1), 7.85);
    EXPECT_FLOAT_EQ(scheduler.GetResult<float>(id2), 2.5);
}

TEST(SchedulerTestSuite, FutureResultTest4) {
    double m = 100.0;
    double n = 50.0;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](double m, double n) { return m - n; }, m, n);
    auto id2 = scheduler.Add([](double m, double n) { return m + n; }, m, scheduler.GetFutureResult<double>(id1));

    scheduler.ExecuteAll();

    EXPECT_DOUBLE_EQ(scheduler.GetResult<double>(id1), 50.0);
    EXPECT_DOUBLE_EQ(scheduler.GetResult<double>(id2), 150.0);
}

TEST(SchedulerTestSuite, FutureResultTest5) {
    int x = 10;
    int y = 4;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](int x, int y) { return x % y; }, x, y);
    auto id2 = scheduler.Add([](int x, int y) { return x / y; }, x, scheduler.GetFutureResult<int>(id1));

    scheduler.ExecuteAll();

    EXPECT_EQ(scheduler.GetResult<int>(id1), 2);
    EXPECT_EQ(scheduler.GetResult<int>(id2), 5);
}

TEST(SchedulerTestSuite, FutureResultTest6) {
    double a = 4.0;
    double b = 2.0;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](double a, double b) { return a * b; }, a, b);
    auto id2 = scheduler.Add([](double a, double b) { return a / b; }, a, scheduler.GetFutureResult<double>(id1));

    scheduler.ExecuteAll();

    EXPECT_DOUBLE_EQ(scheduler.GetResult<double>(id1), 8.0);
    EXPECT_DOUBLE_EQ(scheduler.GetResult<double>(id2), 0.5);
}

TEST(SchedulerTestSuite, FutureResultTest7) {
    int x = 10;
    int y = 2;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](int x, int y) { return x * y; }, x, y);
    auto id2 = scheduler.Add([](int x, int y) { return x - y; }, x, scheduler.GetFutureResult<int>(id1));

    scheduler.ExecuteAll();

    EXPECT_EQ(scheduler.GetResult<int>(id1), 20);
    EXPECT_EQ(scheduler.GetResult<int>(id2), -10);
}

TEST(SchedulerTestSuite, FutureResultTest8) {
    double a = 10.0;
    double b = 2.0;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](double a, double b) { return a / b; }, a, b);
    auto id2 = scheduler.Add([](double a, double b) { return a - b; }, a, scheduler.GetFutureResult<double>(id1));

    scheduler.ExecuteAll();

    EXPECT_DOUBLE_EQ(scheduler.GetResult<double>(id1), 5.0);
    EXPECT_DOUBLE_EQ(scheduler.GetResult<double>(id2), 5.0);
}

TEST(SchedulerTestSuite, FutureResultTest9) {
    int x = 15;
    int y = 3;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](int x, int y) { return x % y; }, x, y);
    auto id2 = scheduler.Add([](int x, int y) { return x + y; }, x, scheduler.GetFutureResult<int>(id1));

    scheduler.ExecuteAll();

    EXPECT_EQ(scheduler.GetResult<int>(id1), 0);
    EXPECT_EQ(scheduler.GetResult<int>(id2), 15);
}

TEST(SchedulerTestSuite, FutureResultTest10) {
    int x = 20;
    int y = 4;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](int x, int y) { return x - y; }, x, y);
    auto id2 = scheduler.Add([](int x, int y) { return x * y; }, x, scheduler.GetFutureResult<int>(id1));

    scheduler.ExecuteAll();

    EXPECT_EQ(scheduler.GetResult<int>(id1), 16);
    EXPECT_EQ(scheduler.GetResult<int>(id2), 320);
}

TEST(SchedulerTestSuite, CommonTest) {
    int x = 5;
    int y = 4;

    TTaskScheduler scheduler;

    auto id1 = scheduler.Add([](int x, int y) { return x * y; }, x, y);
    auto id2 = scheduler.Add([](int x, int y) { return x * y; }, x, scheduler.GetFutureResult<int>(id1));
    auto id3 = scheduler.Add([](int x) { return std::sqrt(x); }, scheduler.GetFutureResult<int>(id2));

    auto id4 = scheduler.Add([](int x) { return x * x; }, y);
    auto id5 = scheduler.Add([](int x, int y){ return x * y; }, scheduler.GetFutureResult<int>(id4), scheduler.GetFutureResult<int>(id3));

    scheduler.ExecuteAll();

    EXPECT_EQ(scheduler.GetResult<int>(id1), 20);
    EXPECT_EQ(scheduler.GetResult<int>(id2), 100);
    EXPECT_EQ(scheduler.GetResult<int>(id3), 10);
    EXPECT_EQ(scheduler.GetResult<int>(id4), 16);
    EXPECT_EQ(scheduler.GetResult<int>(id5), 160);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
