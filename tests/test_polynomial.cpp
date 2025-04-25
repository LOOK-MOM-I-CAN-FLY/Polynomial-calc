#include <gtest/gtest.h>
#include "../polynomial.h"

// Тесты для класса Polynomial

// Тест конструктора по умолчанию
TEST(PolynomialTest, DefaultConstructor) {
    Polynomial<int> p;
    EXPECT_EQ(p.degree(), -1);
    EXPECT_TRUE(p.coeffs.empty());
}

// Тест конструктора с вектором коэффициентов
TEST(PolynomialTest, VectorConstructor) {
    std::vector<int> coeffs = {1, 2, 3};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p.degree(), 2);
    EXPECT_EQ(p.coeffs.size(), 3);
    EXPECT_EQ(p.coeffs[0], 1);
    EXPECT_EQ(p.coeffs[1], 2);
    EXPECT_EQ(p.coeffs[2], 3);
}

// Тест конструктора с константой
TEST(PolynomialTest, ConstantConstructor) {
    Polynomial<int> p(5);
    EXPECT_EQ(p.degree(), 0);
    EXPECT_EQ(p.coeffs.size(), 1);
    EXPECT_EQ(p.coeffs[0], 5);
}

// Тест нормализации многочлена
TEST(PolynomialTest, Normalize) {
    std::vector<int> coeffs = {1, 2, 3, 0, 0};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p.degree(), 2);
    EXPECT_EQ(p.coeffs.size(), 3);
}

// Тест для нормализации нулевого многочлена
TEST(PolynomialTest, NormalizeZero) {
    std::vector<int> coeffs = {0, 0, 0};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p.degree(), -1);
    EXPECT_TRUE(p.coeffs.empty());
}

// Тест степени многочлена
TEST(PolynomialTest, Degree) {
    std::vector<int> coeffs = {1, 2, 3, 4};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p.degree(), 3);
}

// Тест доступа по индексу
TEST(PolynomialTest, IndexOperator) {
    std::vector<int> coeffs = {1, 2, 3};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p[0], 1);
    EXPECT_EQ(p[1], 2);
    EXPECT_EQ(p[2], 3);
    EXPECT_EQ(p[3], 0);  // За пределами определенных коэффициентов
    EXPECT_EQ(p[-1], 0); // За пределами определенных коэффициентов
} 