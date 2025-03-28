#include <gtest/gtest.h>
#include "../modint.h"

// Тесты для класса ModInt

// Тест конструктора
TEST(ModIntTest, Constructor) {
    ModInt<7> a(3);
    EXPECT_EQ(a.value, 3);
    
    ModInt<7> b(10); // 10 % 7 = 3
    EXPECT_EQ(b.value, 3);
    
    ModInt<7> c(-4); // -4 % 7 = 3 в кольце
    EXPECT_EQ(c.value, 3);
}

// Тест сложения
TEST(ModIntTest, Addition) {
    ModInt<7> a(3);
    ModInt<7> b(5);
    ModInt<7> c = a + b; // (3 + 5) % 7 = 1
    EXPECT_EQ(c.value, 1);
    
    a += b; // a = (3 + 5) % 7 = 1
    EXPECT_EQ(a.value, 1);
}

// Тест вычитания
TEST(ModIntTest, Subtraction) {
    ModInt<7> a(3);
    ModInt<7> b(5);
    ModInt<7> c = a - b; // (3 - 5) % 7 = -2 % 7 = 5
    EXPECT_EQ(c.value, 5);
    
    a -= b; // a = (3 - 5) % 7 = -2 % 7 = 5
    EXPECT_EQ(a.value, 5);
}

// Тест умножения
TEST(ModIntTest, Multiplication) {
    ModInt<7> a(3);
    ModInt<7> b(5);
    ModInt<7> c = a * b; // (3 * 5) % 7 = 15 % 7 = 1
    EXPECT_EQ(c.value, 1);
    
    a *= b; // a = (3 * 5) % 7 = 15 % 7 = 1
    EXPECT_EQ(a.value, 1);
}

// Тест быстрого возведения в степень
TEST(ModIntTest, Power) {
    ModInt<7> a(3);
    ModInt<7> result = a.pow(4); // 3^4 % 7 = 81 % 7 = 4
    EXPECT_EQ(result.value, 4);
    
    // Проверка для особых случаев
    result = a.pow(0); // 3^0 = 1
    EXPECT_EQ(result.value, 1);
    
    result = a.pow(1); // 3^1 = 3
    EXPECT_EQ(result.value, 3);
}

// Тест нахождения обратного элемента
TEST(ModIntTest, Inverse) {
    ModInt<7> a(3);
    ModInt<7> inv = a.inv(); // 3 * inv ≡ 1 (mod 7) => inv = 5
    EXPECT_EQ(inv.value, 5);
    
    // Проверка: a * inv = 1
    ModInt<7> product = a * inv;
    EXPECT_EQ(product.value, 1);
}

// Тест деления
TEST(ModIntTest, Division) {
    ModInt<7> a(3);
    ModInt<7> b(2);
    ModInt<7> result = a / b; // 3 / 2 = 3 * (2^(-1)) = 3 * 4 = 12 % 7 = 5
    EXPECT_EQ(result.value, 5);
    
    a /= b; // a = 3 / 2 = 5
    EXPECT_EQ(a.value, 5);
}

// Тест равенства
TEST(ModIntTest, Equality) {
    ModInt<7> a(3);
    ModInt<7> b(3);
    ModInt<7> c(10); // 10 % 7 = 3
    ModInt<7> d(4);
    
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a == c);
    EXPECT_FALSE(a == d);
    
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a != c);
    EXPECT_TRUE(a != d);
} 