#include <gtest/gtest.h>
#include "main.cpp" // Замените на имя вашего файла с реализацией

// Тесты для UniquePtr
TEST(UniquePtrTest, BasicFunctionality) {
    UniquePtr<int> uptr(new int(42));
    EXPECT_EQ(*uptr, 42);
}

TEST(UniquePtrTest, MoveSemantics) {
    UniquePtr<int> uptr1(new int(42));
    UniquePtr<int> uptr2 = std::move(uptr1); // Перемещение

    EXPECT_EQ(*uptr2, 42);
    EXPECT_EQ(uptr1.get(), nullptr); // uptr1 должен быть пустым
}

TEST(UniquePtrTest, Reset) {
    UniquePtr<int> uptr(new int(42));
    uptr.reset(new int(100));
    EXPECT_EQ(*uptr, 100);
}

// Тесты для SharedPtr
TEST(SharedPtrTest, BasicFunctionality) {
    SharedPtr<int> sptr(new int(42));
    EXPECT_EQ(*sptr, 42);
    EXPECT_EQ(sptr.use_count(), 1);
}

TEST(SharedPtrTest, CopySemantics) {
    SharedPtr<int> sptr1(new int(42));
    SharedPtr<int> sptr2(sptr1); // Копирование

    EXPECT_EQ(*sptr1, 42);
    EXPECT_EQ(*sptr2, 42);
    EXPECT_EQ(sptr1.use_count(), 2);
}

TEST(SharedPtrTest, MoveSemantics) {
    SharedPtr<int> sptr1(new int(42));
    SharedPtr<int> sptr2 = std::move(sptr1); // Перемещение

    EXPECT_EQ(*sptr2, 42);
    EXPECT_EQ(sptr1.get(), nullptr); // sptr1 должен быть пустым
}

TEST(SharedPtrTest, Reset) {
    SharedPtr<int> sptr(new int(42));
    sptr.reset(new int(100));

    EXPECT_EQ(*sptr, 100);
    EXPECT_EQ(sptr.use_count(), 1); // После сброса счетчик должен быть 1
}

// Тест на правильное освобождение памяти
TEST(SharedPtrTest, ReleaseMemory) {
    {
        SharedPtr<int> sptr(new int(42));
        EXPECT_EQ(sptr.use_count(), 1);
        {
            SharedPtr<int> sptr2 = sptr; // Копирование
            EXPECT_EQ(sptr.use_count(), 2);
        } // sptr2 выходит из области видимости здесь
        EXPECT_EQ(sptr.use_count(), 1); // Счетчик должен уменьшиться до 1
    }
}

// Основная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}