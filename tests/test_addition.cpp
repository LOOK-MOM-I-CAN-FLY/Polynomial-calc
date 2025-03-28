#include <gtest/gtest.h>
#include "../polynomial.h"

// Тесты операции сложения многочленов

// Сложение двух обычных многочленов
TEST(PolynomialAdditionTest, RegularPolynomials) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {4, 5, 6}; // 4 + 5x + 6x^2
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 + p2;
    EXPECT_EQ(result.degree(), 2);
    EXPECT_EQ(result[0], 5);  // 1 + 4
    EXPECT_EQ(result[1], 7);  // 2 + 5
    EXPECT_EQ(result[2], 9);  // 3 + 6
}

// Сложение многочленов разной степени
TEST(PolynomialAdditionTest, DifferentDegrees) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {4, 5};    // 4 + 5x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 + p2;
    EXPECT_EQ(result.degree(), 2);
    EXPECT_EQ(result[0], 5);  // 1 + 4
    EXPECT_EQ(result[1], 7);  // 2 + 5
    EXPECT_EQ(result[2], 3);  // 3 (нет члена в p2)
}

// Сложение с нулевым многочленом
TEST(PolynomialAdditionTest, AddZeroPolynomial) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {}; // Нулевой многочлен
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 + p2;
    EXPECT_EQ(result.degree(), 2);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

// Сложение многочленов с отрицательными коэффициентами
TEST(PolynomialAdditionTest, NegativeCoefficients) {
    std::vector<int> coeffs1 = {-1, -2, -3}; // -1 - 2x - 3x^2
    std::vector<int> coeffs2 = {1, 2, 3};    // 1 + 2x + 3x^2
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> result = p1 + p2;
    EXPECT_EQ(result.degree(), -1); // должно получиться 0 (нулевой многочлен)
    EXPECT_TRUE(result.coeffs.empty());
}

// Проверка оператора +=
TEST(PolynomialAdditionTest, PlusEqualsOperator) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {4, 5, 6}; // 4 + 5x + 6x^2
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    p1 += p2;
    EXPECT_EQ(p1.degree(), 2);
    EXPECT_EQ(p1[0], 5);  // 1 + 4
    EXPECT_EQ(p1[1], 7);  // 2 + 5
    EXPECT_EQ(p1[2], 9);  // 3 + 6
} 