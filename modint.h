/** @file modint.h
 *  @brief Шаблон класса для работы с целыми числами по простому модулю P с полной арифметикой.
 *
 *  Предполагается, что P — простое число.
 *  Используется во всех остальных модулях библиотеки для
 *  вычислений в поле остатков по модулю P.
 */
#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <tuple>
#include <algorithm>

/// @cond INTERNAL
using namespace std;
/// @endcond


//////////////////////////////
// modint.h
//////////////////////////////


/**
 * @class ModInt
 * @tparam MOD простое модульное основание P.
 * @brief Класс для работы с остатками по модулю P.
 *
 * Особенности реализации:
 * - безопасное сложение и вычитание без выхода за диапазон;
 * - умножение с приведением через long long;
 * - обратный элемент вычисляется быстрым возведением в степень (по малой теореме Ферма).
 */
template<int MOD>
struct ModInt {

    /// Остаток в диапазоне от 0 до P-1.
    int value;

    /// Значение модуля (constexpr) — полезно в шаблонах.
    static constexpr int MOD_VALUE = MOD;
    
    /** @name Конструкторы и базовые операции */
    ///@{
    /// Конструктор по целому числу
    ModInt(int v = 0) {
        value = v % MOD;
        if (value < 0)
            value += MOD;
    }
    /// Копирующий конструктор
    ModInt(const ModInt &other) : value(other.value) {}

    /// Оператор +=
    ModInt& operator+=(const ModInt &other) {
        value += other.value;
        if(value >= MOD)
            value -= MOD;
        return *this;
    }
    /// Оператор -=
    ModInt& operator-=(const ModInt &other) {
        value -= other.value;
        if(value < 0)
            value += MOD;
        return *this;
    }
    /// Оператор *=
    ModInt& operator*=(const ModInt &other) {
        value = (int)((long long)value * other.value % MOD);
        return *this;
    }
    /// Оператор /=
    ModInt& operator/=(const ModInt &other) {
        *this *= other.inv();
        return *this;
    }
    ///@}

    /// Возведение в степень (быстрое возведение в степень).
    ModInt pow(long long exp) const {
        ModInt base = *this;
        ModInt result(1);
        while(exp > 0) {
            if(exp & 1)
                result *= base;
            base *= base;
            exp /= 2;
        }
        return result;
    }

    /// Мультипликативная инверсия (предполагается, что MOD — простое).
    ModInt inv() const {
        return pow(MOD - 2);
    }
    
    /* -------------------- дружественные free-функции -------------------- */
    friend ModInt operator+(ModInt a, const ModInt &b) { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt &b) { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt &b) { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt &b) { return a /= b; }
    
    /// Оператор вывода в поток
    friend ostream& operator<<(ostream &os, const ModInt &m) {
        os << m.value;
        return os;
    }
    /// Оператор сравнения ==
    friend bool operator==(const ModInt &a, const ModInt &b) {
        return a.value == b.value;
    }
    /// Оператор сравнения !=
    friend bool operator!=(const ModInt &a, const ModInt &b) {
        return a.value != b.value;
    }
};
