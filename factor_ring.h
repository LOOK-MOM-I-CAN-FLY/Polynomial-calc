#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <tuple>
#include <algorithm>
#include <functional>
#include "polynomial.h"
#include "modint.h"

using namespace std;

//////////////////////////////
// Factor Ring Element
//////////////////////////////

template<typename T>
class FactorRingElement {
public:
    Polynomial<T> poly;     // Многочлен, представляющий элемент.
    Polynomial<T> mod_poly; // Модульный многочлен (идеал).

    FactorRingElement(const Polynomial<T>& poly, const Polynomial<T>& mod_poly)
        : mod_poly(mod_poly)
    {
        this->poly = poly % mod_poly;
    }
    // Конструктор по умолчанию (единичный элемент).
    FactorRingElement() : mod_poly(Polynomial<T>(T(1))) {}

    FactorRingElement operator+(const FactorRingElement& other) const {
        if(mod_poly.coeffs != other.mod_poly.coeffs)
            throw runtime_error("Different modules in the quotient ring when added together");
        return FactorRingElement(poly + other.poly, mod_poly);
    }
    
    FactorRingElement operator-(const FactorRingElement& other) const {
        if(mod_poly.coeffs != other.mod_poly.coeffs)
            throw runtime_error("Different modules in the factor ring during subtraction");
        return FactorRingElement(poly - other.poly, mod_poly);
    }
    
    FactorRingElement operator*(const FactorRingElement& other) const {
        if(mod_poly.coeffs != other.mod_poly.coeffs)
            throw runtime_error("Different modules in the factor ring during multiplication");
        return FactorRingElement(poly * other.poly, mod_poly);
    }
    
    // Расширенный алгоритм Евклида для многочленов:
    // Находит x и y такие, что a*x + b*y == gcd(a, b)
    static tuple<Polynomial<T>, Polynomial<T>, Polynomial<T>> extended_gcd(
        const Polynomial<T>& a, const Polynomial<T>& b)
    {
        if(b.degree() < 0) {
            return {a, Polynomial<T>(T(1)), Polynomial<T>(T(0))};
        }
        auto [q, r] = a.divmod(b);
        auto [g, x, y] = extended_gcd(b, r);
        return {g, y, x - q * y};
    }
    
    // Вычисляет обратный элемент в фактор-кольце, если он существует.
    FactorRingElement inv() const {
        auto [g, x, y] = extended_gcd(poly, mod_poly);
        if(g.degree() != 0)
            throw runtime_error("The inverse element does not exist in this quotient ring.");
        T inv_g = g.coeffs[0].inv(); // Предполагается, что тип T имеет метод inv()
        return FactorRingElement(x * Polynomial<T>(inv_g), mod_poly);
    }
    
    FactorRingElement operator/(const FactorRingElement& other) const {
        if(mod_poly.coeffs != other.mod_poly.coeffs)
            throw runtime_error("Different modules in the quotient ring during division");
        return *this * other.inv();
    }
    
    FactorRingElement pow(unsigned int exponent) const {
        FactorRingElement result(Polynomial<T>(T(1)), mod_poly);
        FactorRingElement base = *this;
        while(exponent) {
            if(exponent & 1)
                result = result * base;
            base = base * base;
            exponent >>= 1;
        }
        return result;
    }
    
    friend ostream& operator<<(ostream &os, const FactorRingElement& elem) {
        os << elem.poly;
        return os;
    }
};

//////////////////////////////
// Irreducibility Check
//////////////////////////////

template<typename T>
bool is_irreducible(const Polynomial<T>& poly) {
    int deg = poly.degree();
    if(deg <= 0)
        return false;
    if(deg == 1)
        return true;
    int field_mod = T::MOD_VALUE;
    for (int d = 1; d <= deg / 2; d++) {
        vector<T> coeffs(d, T(0));
        function<bool(int)> gen = [&](int pos) -> bool {
            if (pos == d) {
                vector<T> candidate_coeffs = coeffs;
                candidate_coeffs.push_back(T(1)); // делаем ведущий коэффициент равным 1
                Polynomial<T> candidate(candidate_coeffs);
                auto rem = poly.divmod(candidate).second;
                if(rem.degree() < 0)
                    return true; // найден делитель -> многочлен приводим.
                return false;
            }
            for (int i = 0; i < field_mod; i++) {
                coeffs[pos] = T(i);
                if (gen(pos + 1))
                    return true;
            }
            return false;
        };
        if(gen(0))
            return false;
    }
    return true;
}

//////////////////////////////
// Функции ввода многочленов
//////////////////////////////

// Оригинальная функция для ввода многочлена (коэффициенты вводятся начиная с константного члена)
template<typename T>
Polynomial<T> read_polynomial() {
    int n;
    cout << "Enter the number of coefficients: ";
    cin >> n;
    vector<T> coeffs(n);
    cout << "Enter the coefficients (constant term first): ";
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        coeffs[i] = T(tmp);
    }
    return Polynomial<T>(coeffs);
}

// Функция для ввода многочлена с ограничением по количеству коэффициентов (не более max_coeffs)
template<typename T>
Polynomial<T> read_polynomial_restricted(int max_coeffs) {
    int n;
    do {
        cout << "Enter the number of coefficients (max " << max_coeffs << "): ";
        cin >> n;
        if(n > max_coeffs)
            cout << "Error: the number of coefficients should not exceed " << max_coeffs << ".\n";
    } while(n > max_coeffs);
    vector<T> coeffs(n);
    cout << "Enter the coefficients (constant term first): ";
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        coeffs[i] = T(tmp);
    }
    return Polynomial<T>(coeffs);
}

//////////////////////////////
// Factor Ring Operations (Field Extension F[x]/(f(x)))
//////////////////////////////

template<int P>
void run_factor_ring() {
    typedef ModInt<P> Field;
    cout << "\nFactor ring operations over field Z" << P << ":\n";
    
    // Ввод многочлена f(x) для факторизации и проверка его неприводимости.
    Polynomial<Field> f;
    bool irreducible_valid = false;
    while(!irreducible_valid) {
        cout << "Enter the polynomial f(x) (coefficients as constant term first):\n";
        f = read_polynomial<Field>();  
        if(is_irreducible(f)) {
            irreducible_valid = true;
        } else {
            cout << "The polynomial f(x) is reducible over Z" << P
                 << ". Please enter an irreducible polynomial.\n";
        }
    }
    
    int n = f.degree();
    cout << "\nYou entered a polynomial f(x) = " << f << " degree " << n << ".\n";
    //cout << "Элементы фактор-кольца будут иметь вид (a + b*x + ...), где степень многочлена не превышает " << n - 1 << ".\n";
    
    // Ввод элементов фактор-кольца с ограничением по степени
    cout << "\nEnter the first element of the quotient ring:\n";
    Polynomial<Field> a = read_polynomial_restricted<Field>(n);
    cout << "Enter the second element of the quotient ring:\n";
    Polynomial<Field> b = read_polynomial_restricted<Field>(n);
    
    FactorRingElement<Field> elem1(a, f);
    FactorRingElement<Field> elem2(b, f);
    
    cout << "\nElement A = " << elem1 << "\n";
    cout << "Element B = " << elem2 << "\n";
    
    // Меню операций над элементами фактор-кольца
    cout << "\nChoose operation:\n";
    cout << "1. A + B\n";
    cout << "2. A - B\n";
    cout << "3. A * B\n";
    cout << "4. A / B\n";
    cout << "5. Inverse element A\n";
    cout << "6. A^n (exponentiation)\n";
    cout << "Your choice: ";
    int op;
    cin >> op;
    switch(op) {
        case 1:
            cout << "\nA + B = " << (elem1 + elem2) << "\n";
            break;
        case 2:
            cout << "\nA - B = " << (elem1 - elem2) << "\n";
            break;
        case 3:
            cout << "\nA * B = " << (elem1 * elem2) << "\n";
            break;
        case 4:
            try {
                cout << "\nA / B = " << (elem1 / elem2) << "\n";
            } catch(const runtime_error &e) {
                cout << "\nDivision error: " << e.what() << "\n";
            }
            break;
        case 5:
            try {
                cout << "\nInverse element A = " << elem1.inv() << "\n";
            } catch(const runtime_error &e) {
                cout << "\nError when calculating the inverse element: " << e.what() << "\n";
            }
            break;
        case 6: {
            int exponent;
            cout << "Enter a non-negative integer power: ";
            cin >> exponent;
            cout << "\nA^" << exponent << " = " << elem1.pow(exponent) << "\n";
            break;
        }
        default:
            cout << "\nUnknown operation!\n";
            break;
    }
}
