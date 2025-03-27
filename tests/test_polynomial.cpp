#include "gtest/gtest.h"
#include "polynomial.h"
#include "modint.h"
#include "factor_ring.h"

// Пример теста для сложения полиномов с коэффициентами типа double
TEST(PolynomialTest, Addition) {
    // p(x) = 2x + 1
    Polynomial<double> p({1, 2});
    // q(x) = 4x + 3
    Polynomial<double> q({3, 4});
    // Ожидаем: 6x + 4
    Polynomial<double> expected({4, 6});
    
    Polynomial<double> result = p + q;
    ASSERT_EQ(result.coeffs.size(), expected.coeffs.size());
    for (size_t i = 0; i < expected.coeffs.size(); i++) {
        EXPECT_DOUBLE_EQ(result.coeffs[i], expected.coeffs[i]);
    }
}

// Дополнительные тесты можно добавить для проверки операций вычитания, умножения, деления и возведения в степень.

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
