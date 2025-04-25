#include <gtest/gtest.h>
#include "../polynomial.h"

// Тесты операции умножения многочленов

// Умножение двух обычных многочленов
TEST(PolynomialMultiplicationTest, RegularPolynomials) {
    std::vector<int> coeffs1 = {1, 2}; // 1 + 2x
    std::vector<int> coeffs2 = {3, 4}; // 3 + 4x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 * p2;
    EXPECT_EQ(result.degree(), 2);
    EXPECT_EQ(result[0], 3);   // 1*3
    EXPECT_EQ(result[1], 10);  // 1*4 + 2*3
    EXPECT_EQ(result[2], 8);   // 2*4
}

// Умножение многочленов разной степени
TEST(PolynomialMultiplicationTest, DifferentDegrees) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {4, 5};    // 4 + 5x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 * p2;
    EXPECT_EQ(result.degree(), 3);
    EXPECT_EQ(result[0], 4);   // 1*4
    EXPECT_EQ(result[1], 13);  // 1*5 + 2*4
    EXPECT_EQ(result[2], 22);  // 2*5 + 3*4
    EXPECT_EQ(result[3], 15);  // 3*5
}

// Умножение на нулевой многочлен
TEST(PolynomialMultiplicationTest, MultiplyByZero) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {}; // Нулевой многочлен
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 * p2;
    EXPECT_EQ(result.degree(), -1); // должно получиться 0 (нулевой многочлен)
    EXPECT_TRUE(result.coeffs.empty());
}

// Умножение на единичный многочлен
TEST(PolynomialMultiplicationTest, MultiplyByOne) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {1}; // 1 (единичный многочлен)
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 * p2;
    EXPECT_EQ(result.degree(), 2);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

// Умножение на x (сдвиг)
TEST(PolynomialMultiplicationTest, MultiplyByX) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {0, 1}; // x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 * p2;
    EXPECT_EQ(result.degree(), 3);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 2);
    EXPECT_EQ(result[3], 3);
}

// Проверка оператора *=
TEST(PolynomialMultiplicationTest, TimesEqualsOperator) {
    std::vector<int> coeffs1 = {1, 2}; // 1 + 2x
    std::vector<int> coeffs2 = {3, 4}; // 3 + 4x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    p1 *= p2;
    EXPECT_EQ(p1.degree(), 2);
    EXPECT_EQ(p1[0], 3);   // 1*3
    EXPECT_EQ(p1[1], 10);  // 1*4 + 2*3
    EXPECT_EQ(p1[2], 8);   // 2*4
} 