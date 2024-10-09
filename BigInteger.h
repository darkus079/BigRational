#pragma once
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class BigInteger {
private:
    vector<int> _digits;
    bool _isNegative;
    friend void swap(BigInteger &a, BigInteger &b);
    void normalize();

public:
    BigInteger(int a = 0);
    BigInteger(const string s);
    BigInteger(const char* s);
    BigInteger(const BigInteger& num) = default;
    ~BigInteger() = default;
    BigInteger& operator+=(BigInteger a);
    BigInteger& operator-=(BigInteger a);
    BigInteger& operator*=(BigInteger a);
    BigInteger& operator/=(BigInteger a);
    BigInteger& operator%=(BigInteger a);
    BigInteger& operator=(BigInteger a);
    BigInteger operator+(BigInteger a) const;
    BigInteger operator-(BigInteger a) const;
    BigInteger operator*(BigInteger a) const;
    BigInteger operator/(BigInteger a) const;
    BigInteger operator%(BigInteger a) const;
    BigInteger operator-();
    BigInteger& operator++();
    BigInteger& operator--();
    BigInteger operator++(int);
    BigInteger operator--(int);
    friend bool operator==(const BigInteger& a, const BigInteger& b);
    friend bool operator!=(const BigInteger& a, const BigInteger& b);
    friend bool operator<(const BigInteger& a, const BigInteger& b);
    friend bool operator<=(const BigInteger& a, const BigInteger& b);
    friend bool operator>(const BigInteger& a, const BigInteger& b);
    friend bool operator>=(const BigInteger& a, const BigInteger& b);
    string toString() const;
    friend std::istream& operator>>(std::istream&, BigInteger& num);
    friend std::ostream& operator<<(std::ostream&, const BigInteger& num);
    friend BigInteger abs(BigInteger a);
    explicit operator bool() const;
};