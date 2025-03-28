#include <gtest/gtest.h>
#include "../polynomial.h"

// Тесты операции вычитания многочленов

// Вычитание двух обычных многочленов
TEST(PolynomialSubtractionTest, RegularPolynomials) {
    std::vector<int> coeffs1 = {5, 7, 9}; // 5 + 7x + 9x^2
    std::vector<int> coeffs2 = {1, 2, 3}; // 1 + 2x + 3x^2
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 - p2;
    EXPECT_EQ(result.degree(), 2);
    EXPECT_EQ(result[0], 4);  // 5 - 1
    EXPECT_EQ(result[1], 5);  // 7 - 2
    EXPECT_EQ(result[2], 6);  // 9 - 3
}

// Вычитание многочленов разной степени
TEST(PolynomialSubtractionTest, DifferentDegrees) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {4, 5};    // 4 + 5x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 - p2;
    EXPECT_EQ(result.degree(), 2);
    EXPECT_EQ(result[0], -3);  // 1 - 4
    EXPECT_EQ(result[1], -3);  // 2 - 5
    EXPECT_EQ(result[2], 3);   // 3 (нет члена в p2)
}

// Вычитание с нулевым многочленом
TEST(PolynomialSubtractionTest, SubtractZeroPolynomial) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {}; // Нулевой многочлен
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 - p2;
    EXPECT_EQ(result.degree(), 2);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

// Вычитание из нулевого многочлена
TEST(PolynomialSubtractionTest, ZeroSubtractPolynomial) {
    std::vector<int> coeffs1 = {}; // Нулевой многочлен
    std::vector<int> coeffs2 = {1, 2, 3}; // 1 + 2x + 3x^2
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 - p2;
    EXPECT_EQ(result.degree(), 2);
    EXPECT_EQ(result[0], -1);
    EXPECT_EQ(result[1], -2);
    EXPECT_EQ(result[2], -3);
}

// Вычитание одинаковых многочленов
TEST(PolynomialSubtractionTest, SubtractEqualPolynomials) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs1);
    Polynomial<int> result = p1 - p2;
    EXPECT_EQ(result.degree(), -1); // должно получиться 0 (нулевой многочлен)
    EXPECT_TRUE(result.coeffs.empty());
}

// Проверка оператора -=
TEST(PolynomialSubtractionTest, MinusEqualsOperator) {
    std::vector<int> coeffs1 = {5, 7, 9}; // 5 + 7x + 9x^2
    std::vector<int> coeffs2 = {1, 2, 3}; // 1 + 2x + 3x^2
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    p1 -= p2;
    EXPECT_EQ(p1.degree(), 2);
    EXPECT_EQ(p1[0], 4);  // 5 - 1
    EXPECT_EQ(p1[1], 5);  // 7 - 2
    EXPECT_EQ(p1[2], 6);  // 9 - 3
} 