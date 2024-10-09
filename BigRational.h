#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "BigInteger.h"

using std::vector;
using std::string;

class BigRational {
private:
    BigInteger _num, _denom;
    bool _isNegative;
    friend BigInteger gcd(BigInteger a, BigInteger b);
    void reduce();

public:
    BigRational(BigInteger a);
    BigRational(BigInteger num, BigInteger denom);
    BigRational(int a = 0);
    BigRational(const BigRational& a) = default;
    ~BigRational() = default;
    BigRational operator+(BigRational a) const;
    BigRational operator-(BigRational a) const;
    BigRational operator*(BigRational a) const;
    BigRational operator/(BigRational a) const;
    BigRational& operator+=(BigRational a);
    BigRational& operator-=(BigRational a);
    BigRational& operator*=(BigRational a);
    BigRational& operator/=(BigRational a);
    BigRational operator-() const;
    friend bool operator<(const BigRational& a, const BigRational b);
    friend bool operator<=(const BigRational& a, const BigRational b);
    friend bool operator>(const BigRational& a, const BigRational b);
    friend bool operator>=(const BigRational& a, const BigRational b);
    friend bool operator==(const BigRational& a, const BigRational b);
    friend bool operator!=(const BigRational& a, const BigRational b);
    explicit operator double() const;
    explicit operator bool() const;
    string toString() const;
    string asDecimal(size_t precision = 0) const;
    friend std::istream& operator>>(std::istream& in, BigRational& a);
};