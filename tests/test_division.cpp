#include <gtest/gtest.h>
#include "../polynomial.h"

// Тесты операции деления многочленов

// Деление двух обычных многочленов
TEST(PolynomialDivisionTest, RegularPolynomials) {
    std::vector<int> coeffs1 = {-4, 0, 1}; // -4 + x^2
    std::vector<int> coeffs2 = {-2, 1};    // -2 + x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    auto [quotient, remainder] = p1.divmod(p2);
    
    EXPECT_EQ(quotient.degree(), 1);
    EXPECT_EQ(quotient[0], 2);  // частное: 2 + x
    EXPECT_EQ(quotient[1], 1);
    
    EXPECT_EQ(remainder.degree(), -1); // остаток: 0
    EXPECT_TRUE(remainder.coeffs.empty());
}

// Деление с нетривиальным остатком
TEST(PolynomialDivisionTest, DivisionWithRemainder) {
    std::vector<int> coeffs1 = {1, 1, 1}; // 1 + x + x^2
    std::vector<int> coeffs2 = {1, 1};    // 1 + x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    auto [quotient, remainder] = p1.divmod(p2);
    
    EXPECT_EQ(quotient.degree(), 1);
    EXPECT_EQ(quotient[0], 0);  // частное: x
    EXPECT_EQ(quotient[1], 1);
    
    EXPECT_EQ(remainder.degree(), 0); // остаток: 1
    EXPECT_EQ(remainder[0], 1);
}

// Деление многочленом большей степени
TEST(PolynomialDivisionTest, DivisionByHigherDegree) {
    std::vector<int> coeffs1 = {1, 2}; // 1 + 2x
    std::vector<int> coeffs2 = {3, 4, 5}; // 3 + 4x + 5x^2
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    auto [quotient, remainder] = p1.divmod(p2);
    
    EXPECT_EQ(quotient.degree(), -1); // частное: 0
    EXPECT_TRUE(quotient.coeffs.empty());
    
    EXPECT_EQ(remainder.degree(), 1); // остаток: 1 + 2x (тот же самый многочлен)
    EXPECT_EQ(remainder[0], 1);
    EXPECT_EQ(remainder[1], 2);
}

// Деление на нуль
TEST(PolynomialDivisionTest, DivisionByZero) {
    std::vector<int> coeffs1 = {1, 2, 3}; // 1 + 2x + 3x^2
    std::vector<int> coeffs2 = {}; // Нулевой многочлен
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    
    EXPECT_THROW(p1.divmod(p2), std::runtime_error);
}

// Деление нуля на многочлен
TEST(PolynomialDivisionTest, ZeroDividedByPolynomial) {
    std::vector<int> coeffs1 = {}; // Нулевой многочлен
    std::vector<int> coeffs2 = {1, 2}; // 1 + 2x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    auto [quotient, remainder] = p1.divmod(p2);
    
    EXPECT_EQ(quotient.degree(), -1); // частное: 0
    EXPECT_TRUE(quotient.coeffs.empty());
    
    EXPECT_EQ(remainder.degree(), -1); // остаток: 0
    EXPECT_TRUE(remainder.coeffs.empty());
}

// Проверка оператора /
TEST(PolynomialDivisionTest, DivisionOperator) {
    std::vector<int> coeffs1 = {-4, 0, 1}; // -4 + x^2
    std::vector<int> coeffs2 = {-2, 1};    // -2 + x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> quotient = p1 / p2;
    
    EXPECT_EQ(quotient.degree(), 1);
    EXPECT_EQ(quotient[0], 2);  // частное: 2 + x
    EXPECT_EQ(quotient[1], 1);
}

// Проверка оператора %
TEST(PolynomialDivisionTest, ModuloOperator) {
    std::vector<int> coeffs1 = {1, 1, 1}; // 1 + x + x^2
    std::vector<int> coeffs2 = {1, 1};    // 1 + x
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(coeffs2);
    Polynomial<int> remainder = p1 % p2;
    
    EXPECT_EQ(remainder.degree(), 0); // остаток: 1
    EXPECT_EQ(remainder[0], 1);
} 