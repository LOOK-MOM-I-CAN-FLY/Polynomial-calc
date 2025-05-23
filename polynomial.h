/** @file polynomial.h
 *  @brief Универсальный шаблон многочлена вида суммы a_i x^i.
 *
 *  Предоставляет:
 *  - арифметику (+, –, *, /, %);
 *  - алгоритм деления с остатком;
 *  - экспоненту и быструю оценку значения многочлена;
 *  - дружественный вывод в поток.
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
// polynomial.h
//////////////////////////////


/**
 * @class Polynomial
 * @tparam T тип коэффициентов (поле или кольцо с операциями +, –, *, /).
 * @brief Класс для работы с разреженными многочленами (хранит только нужное число коэффициентов).
 *
 * Все операции возвращают нормализованный результат
 * (ведущие нулевые коэффициенты автоматически отбрасываются).
 */
template<typename T>
class Polynomial {
public:
    /**
     * @brief Сырые коэффициенты многочлена, где coeffs[i] соответствует x^i.
     */
    vector<T> coeffs;
    
    /** @name Конструкторы */
    ///@{
    /// Конструктор по умолчанию
    Polynomial() {}
    /// Конструктор по вектору коэффициентов
    Polynomial(const vector<T>& c): coeffs(c) {
        normalize();
    }
    /// Конструктор для константного многочлена
    Polynomial(T constant) : coeffs(1, constant) {
        normalize();
    }
    ///@}


    /// Удаляет ведущие нулевые коэффициенты
    void normalize(){
        while(!coeffs.empty() && coeffs.back() == T(0))
            coeffs.pop_back();
    }
    
    /// Возвращает степень многочлена; для нулевого многочлена -1
    int degree() const {
        return coeffs.empty() ? -1 : coeffs.size()-1;
    }
    
    /// Доступ к коэффициенту по индексу; возвращает 0, если индекс вне диапазона
    T operator[](int idx) const {
        return (idx < 0 || idx >= (int)coeffs.size()) ? T(0) : coeffs[idx];
    }
    
    /** @name Арифметика */
    ///@{
    /// Сложение многочленов
    Polynomial operator+(const Polynomial& other) const {
        vector<T> result(max(coeffs.size(), other.coeffs.size()), T(0));
        for (size_t i = 0; i < result.size(); i++) {
            if (i < coeffs.size())
                result[i] = result[i] + coeffs[i];
            if (i < other.coeffs.size())
                result[i] = result[i] + other.coeffs[i];
        }
        return Polynomial(result);
    }
    Polynomial& operator+=(const Polynomial& other) {
        *this = *this + other;
        return *this;
    }
    
    /// Вычитание многочленов
    Polynomial operator-(const Polynomial& other) const {
        vector<T> result(max(coeffs.size(), other.coeffs.size()), T(0));
        for (size_t i = 0; i < result.size(); i++) {
            if (i < coeffs.size())
                result[i] = result[i] + coeffs[i];
            if (i < other.coeffs.size())
                result[i] = result[i] - other.coeffs[i];
        }
        return Polynomial(result);
    }
    Polynomial& operator-=(const Polynomial& other) {
        *this = *this - other;
        return *this;
    }
    
    /// Умножение многочленов
    Polynomial operator*(const Polynomial& other) const {
        if(coeffs.empty() || other.coeffs.empty())
            return Polynomial();
        vector<T> result(coeffs.size() + other.coeffs.size() - 1, T(0));
        for (size_t i = 0; i < coeffs.size(); i++) {
            for (size_t j = 0; j < other.coeffs.size(); j++) {
                result[i+j] = result[i+j] + coeffs[i] * other.coeffs[j];
            }
        }
        return Polynomial(result);
    }
    Polynomial& operator*=(const Polynomial& other) {
        *this = *this * other;
        return *this;
    }
    ///@}
    
    /**
     * @brief Деление с остатком.
     * @returns Пара {частное, остаток}, таких что исходный многочлен = делитель * частное + остаток.
     * @throw std::runtime_error при делении на нулевой многочлен.
     */
    pair<Polynomial, Polynomial> divmod(const Polynomial& divisor) const {
        if(divisor.coeffs.empty())
            throw runtime_error("Division by zero polynomial");
        Polynomial dividend = *this;
        Polynomial quotient;
        quotient.coeffs.resize(max(0, dividend.degree() - divisor.degree() + 1), T(0));
        while(dividend.degree() >= divisor.degree() && dividend.degree() >= 0) {
            int diff = dividend.degree() - divisor.degree();
            T factor = dividend.coeffs.back() / divisor.coeffs.back();
            vector<T> term(diff+1, T(0));
            term[diff] = factor;
            Polynomial<T> monomial(term);
            quotient.coeffs[diff] = factor;
            dividend = dividend - (divisor * monomial);
            dividend.normalize();
        }
        quotient.normalize();
        dividend.normalize();
        return {quotient, dividend};
    }
    
    /// Частное от деления
    Polynomial operator/(const Polynomial& divisor) const {
        return divmod(divisor).first;
    }
    
    /// Остаток от деления
    Polynomial operator%(const Polynomial& divisor) const {
        return divmod(divisor).second;
    }
    
    /// Быстрое возведение в натуральную степень
    Polynomial pow(unsigned int exponent) const {
        Polynomial result(T(1)); 
        Polynomial base = *this;
        while(exponent) {
            if(exponent & 1)
                result = result * base;
            base = base * base;
            exponent >>= 1;
        }
        return result;
    }
    
    /// Вычисляет значение многочлена в точке x методом Горнера
    T evaluate(const T& x) const {
        T result = T(0);
        for (int i = degree(); i >= 0; i--) {
            result = result * x + coeffs[i];
        }
        return result;
    }
    
    /// Человекочитаемый вывод, например 3*x^2 + 2*x + 1
    friend ostream& operator<<(ostream &os, const Polynomial& poly) {
        if(poly.coeffs.empty()){
            os << "0";
            return os;
        }
        bool first = true;
        for(int i = poly.degree(); i >= 0; i--) {
            if(poly.coeffs[i] == T(0))
                continue;
            if(!first)
                os << " + ";
            first = false;
            if(i == 0) {
                os << poly.coeffs[i];
            } else {
                if(poly.coeffs[i] != T(1))
                    os << poly.coeffs[i] << "*";
                os << "x";
                if(i > 1)
                    os << "^" << i;
            }
        }
        if(first)
            os << "0";
        return os;
    }
};
