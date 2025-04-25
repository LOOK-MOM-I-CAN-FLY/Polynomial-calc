#include <gtest/gtest.h>
#include "../factor_ring.h"
#include "../modint.h"
#include "../polynomial.h"

// Тесты для класса FactorRingElement

// Объявление типов для удобства
typedef ModInt<5> Field;  // Поле Z_5
typedef FactorRingElement<Field> FactorRing;

// Подготовка неприводимого многочлена для тестов
Polynomial<Field> get_irreducible_polynomial() {
    // x^2 + 2 - неприводим над Z_5
    std::vector<Field> coeffs = {Field(2), Field(0), Field(1)};
    return Polynomial<Field>(coeffs);
}

// Тест конструктора
TEST(FactorRingTest, Constructor) {
    auto mod_poly = get_irreducible_polynomial();
    
    // Создаем многочлен степени 1: 3 + 4x
    std::vector<Field> coeffs = {Field(3), Field(4)};
    Polynomial<Field> poly(coeffs);
    
    FactorRing element(poly, mod_poly);
    EXPECT_EQ(element.poly.degree(), 1);
    EXPECT_EQ(element.poly[0].value, 3);
    EXPECT_EQ(element.poly[1].value, 4);
    
    // Проверяем, что многочлен большей степени приводится по модулю
    // Создаем x^2 + 1 = -1 (mod x^2 + 2)
    std::vector<Field> high_coeffs = {Field(1), Field(0), Field(1)};
    Polynomial<Field> high_poly(high_coeffs);
    
    FactorRing high_element(high_poly, mod_poly);
    EXPECT_EQ(high_element.poly.degree(), 0);
    EXPECT_EQ(high_element.poly[0].value, 4); // (1 - 2) % 5 = -1 % 5 = 4
}

// Тест сложения
TEST(FactorRingTest, Addition) {
    auto mod_poly = get_irreducible_polynomial();
    
    // 3 + 4x
    std::vector<Field> coeffs1 = {Field(3), Field(4)};
    Polynomial<Field> poly1(coeffs1);
    
    // 2 + x
    std::vector<Field> coeffs2 = {Field(2), Field(1)};
    Polynomial<Field> poly2(coeffs2);
    
    FactorRing elem1(poly1, mod_poly);
    FactorRing elem2(poly2, mod_poly);
    
    // (3 + 4x) + (2 + x) = 5 + 5x = 0 + 0x в Z_5
    FactorRing result = elem1 + elem2;
    EXPECT_EQ(result.poly.degree(), -1);  // нулевой многочлен
    EXPECT_TRUE(result.poly.coeffs.empty());
}

// Тест вычитания
TEST(FactorRingTest, Subtraction) {
    auto mod_poly = get_irreducible_polynomial();
    
    // 3 + 4x
    std::vector<Field> coeffs1 = {Field(3), Field(4)};
    Polynomial<Field> poly1(coeffs1);
    
    // 2 + x
    std::vector<Field> coeffs2 = {Field(2), Field(1)};
    Polynomial<Field> poly2(coeffs2);
    
    FactorRing elem1(poly1, mod_poly);
    FactorRing elem2(poly2, mod_poly);
    
    // (3 + 4x) - (2 + x) = 1 + 3x
    FactorRing result = elem1 - elem2;
    EXPECT_EQ(result.poly.degree(), 1);
    EXPECT_EQ(result.poly[0].value, 1);
    EXPECT_EQ(result.poly[1].value, 3);
}

// Тест умножения
TEST(FactorRingTest, Multiplication) {
    auto mod_poly = get_irreducible_polynomial();
    
    // 3 + 4x
    std::vector<Field> coeffs1 = {Field(3), Field(4)};
    Polynomial<Field> poly1(coeffs1);
    
    // 2 + x
    std::vector<Field> coeffs2 = {Field(2), Field(1)};
    Polynomial<Field> poly2(coeffs2);
    
    FactorRing elem1(poly1, mod_poly);
    FactorRing elem2(poly2, mod_poly);
    
    // (3 + 4x) * (2 + x) = 6 + 11x + 4x^2 = 6 + 11x + 4x^2 (mod 5) = 1 + x + 4x^2
    // Но так как x^2 = -2 (mod x^2 + 2), то 4x^2 = 4 * (-2) = -8 = 2 (mod 5)
    // Итого: (3 + 4x) * (2 + x) = 1 + x + 2 = 3 + x (mod x^2 + 2, Z_5)
    FactorRing result = elem1 * elem2;
    EXPECT_EQ(result.poly.degree(), 1);
    EXPECT_EQ(result.poly[0].value, 3);
    EXPECT_EQ(result.poly[1].value, 1);
}

// Тест для алгоритма Евклида (static метод)
TEST(FactorRingTest, ExtendedGCD) {
    // Тестируем для простых многочленов в Z_5
    // p(x) = x + 1, q(x) = x + 2
    std::vector<Field> p_coeffs = {Field(1), Field(1)};
    std::vector<Field> q_coeffs = {Field(2), Field(1)};
    Polynomial<Field> p(p_coeffs);
    Polynomial<Field> q(q_coeffs);
    
    auto [g, x, y] = FactorRing::extended_gcd(p, q);
    
    // НОД(x+1, x+2) = константа в поле (может быть 1 или 4, что равно -1 в Z_5)
    EXPECT_EQ(g.degree(), 0);
    // Проверяем, что g либо 1, либо 4 (что равно -1 в Z_5)
    EXPECT_TRUE(g[0].value == 1 || g[0].value == 4);
    
    // Проверка: p*x + q*y = g
    Polynomial<Field> check = p * x + q * y;
    EXPECT_EQ(check.degree(), 0);
    // Проверяем, что результат равен g
    EXPECT_EQ(check[0].value, g[0].value);
}

// Тест для расчета обратного элемента
TEST(FactorRingTest, Inverse) {
    auto mod_poly = get_irreducible_polynomial();
    
    // 1 + x
    std::vector<Field> coeffs = {Field(1), Field(1)};
    Polynomial<Field> poly(coeffs);
    
    FactorRing elem(poly, mod_poly);
    FactorRing inv = elem.inv();
    
    // Проверка: elem * inv = 1
    FactorRing product = elem * inv;
    EXPECT_EQ(product.poly.degree(), 0);
    EXPECT_EQ(product.poly[0].value, 1);
}

// Тест для деления
TEST(FactorRingTest, Division) {
    auto mod_poly = get_irreducible_polynomial();
    
    // 3 + 4x
    std::vector<Field> coeffs1 = {Field(3), Field(4)};
    Polynomial<Field> poly1(coeffs1);
    
    // 1 + x
    std::vector<Field> coeffs2 = {Field(1), Field(1)};
    Polynomial<Field> poly2(coeffs2);
    
    FactorRing elem1(poly1, mod_poly);
    FactorRing elem2(poly2, mod_poly);
    
    // (3 + 4x) / (1 + x) = (3 + 4x) * (1 + x)^(-1)
    FactorRing result = elem1 / elem2;
    
    // Проверка: result * elem2 = elem1
    FactorRing check = result * elem2;
    EXPECT_EQ(check.poly.degree(), elem1.poly.degree());
    for (int i = 0; i <= check.poly.degree(); i++) {
        EXPECT_EQ(check.poly[i].value, elem1.poly[i].value);
    }
}

// Тест для возведения в степень
TEST(FactorRingTest, Power) {
    auto mod_poly = get_irreducible_polynomial();
    
    // 1 + x
    std::vector<Field> coeffs = {Field(1), Field(1)};
    Polynomial<Field> poly(coeffs);
    
    FactorRing elem(poly, mod_poly);
    
    // (1 + x)^0 = 1
    FactorRing result0 = elem.pow(0);
    EXPECT_EQ(result0.poly.degree(), 0);
    EXPECT_EQ(result0.poly[0].value, 1);
    
    // (1 + x)^1 = 1 + x
    FactorRing result1 = elem.pow(1);
    EXPECT_EQ(result1.poly.degree(), 1);
    EXPECT_EQ(result1.poly[0].value, 1);
    EXPECT_EQ(result1.poly[1].value, 1);
    
    // Проверка для более высоких степеней
    FactorRing result3 = elem.pow(3);
    // Вычисляем (1 + x)^3 явно для проверки
    FactorRing explicitResult = elem * elem * elem;
    EXPECT_EQ(result3.poly.degree(), explicitResult.poly.degree());
    for (int i = 0; i <= result3.poly.degree(); i++) {
        EXPECT_EQ(result3.poly[i].value, explicitResult.poly[i].value);
    }
} 