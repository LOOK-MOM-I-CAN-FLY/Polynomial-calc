#include <gtest/gtest.h>
#include "../polynomial.h"


TEST(PolynomialTest, DefaultConstructor) {
    Polynomial<int> p;
    EXPECT_EQ(p.degree(), -1);
    EXPECT_TRUE(p.coeffs.empty());
}


TEST(PolynomialTest, VectorConstructor) {
    std::vector<int> coeffs = {1, 2, 3};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p.degree(), 2);
    EXPECT_EQ(p.coeffs.size(), 3);
    EXPECT_EQ(p.coeffs[0], 1);
    EXPECT_EQ(p.coeffs[1], 2);
    EXPECT_EQ(p.coeffs[2], 3);
}


TEST(PolynomialTest, ConstantConstructor) {
    Polynomial<int> p(5);
    EXPECT_EQ(p.degree(), 0);
    EXPECT_EQ(p.coeffs.size(), 1);
    EXPECT_EQ(p.coeffs[0], 5);
}


TEST(PolynomialTest, Normalize) {
    std::vector<int> coeffs = {1, 2, 3, 0, 0};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p.degree(), 2);
    EXPECT_EQ(p.coeffs.size(), 3);
}

TEST(PolynomialTest, NormalizeZero) {
    std::vector<int> coeffs = {0, 0, 0};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p.degree(), -1);
    EXPECT_TRUE(p.coeffs.empty());
}


TEST(PolynomialTest, Degree) {
    std::vector<int> coeffs = {1, 2, 3, 4};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p.degree(), 3);
}


TEST(PolynomialTest, IndexOperator) {
    std::vector<int> coeffs = {1, 2, 3};
    Polynomial<int> p(coeffs);
    EXPECT_EQ(p[0], 1);
    EXPECT_EQ(p[1], 2);
    EXPECT_EQ(p[2], 3);
    EXPECT_EQ(p[3], 0);  // За пределами определенных коэффициентов
    EXPECT_EQ(p[-1], 0); // За пределами определенных коэффициентов
} 
