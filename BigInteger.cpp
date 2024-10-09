#include "BigInteger.h"

void BigInteger::normalize()
{
    int ind = _digits.size() - 1;

    while (ind > 0 && _digits[ind] == 0) {
        _digits.pop_back();
        --ind;
    }

    if (_digits.size() == 1 && _digits[0] == 0) {
        _isNegative = false;
    }
}

BigInteger::BigInteger(int a)
{
    if (a < 0) {
        _isNegative = true;
        a = -a;
    }
    else {
        _isNegative = false;
    }

    do {
        _digits.push_back(a % 10);
        a /= 10;
    } while (a > 0);
}

BigInteger::BigInteger(string s)
{
    if (s[0] == '-') {
        _isNegative = true;
        s = s.substr(1);
    }
    else {
        _isNegative = false;
    }

    _digits.resize(s.size());

    for (size_t i = 0; i < _digits.size(); ++i) {
        _digits[i] = s[s.size() - i - 1] - '0';
    }

    (*this).normalize();
}

BigInteger::BigInteger(const char* s): BigInteger(static_cast<string>(s)) { }

BigInteger& BigInteger::operator+=(BigInteger a)
{
    if (_digits.size() < a._digits.size()) {
        _digits.resize(a._digits.size());
    }

    if (a._digits.size() < _digits.size()) {
        a._digits.resize(_digits.size());
    }

    if (_isNegative == a._isNegative) {
        int p = 0;

        for (int i = 0; i < a._digits.size(); ++i) {
            _digits[i] += a._digits[i] + p;
            p = _digits[i] / 10;
            _digits[i] %= 10;
        }

        if (p > 0) {
            _digits.push_back(1);
        }
    }
    else {
        if (abs(*this) < abs(a)) {
            _isNegative = a._isNegative;
            swap(*this, a);
        }

        int p = 0;

        for (int i = 0; i < a._digits.size(); ++i) {
            _digits[i] -= a._digits[i] + p;
            p = 1 - (_digits[i] + 10) / 10;
            _digits[i] = (_digits[i] + 10) % 10;
        }

        for (int i = a._digits.size(); i < _digits.size(); ++i) {
            _digits[i] -= p;
            p = 1 - (_digits[i] + 10) / 10;
            _digits[i] = (_digits[i] + 10) % 10;
        }
    }

    (*this).normalize();
    return *this;
}

BigInteger& BigInteger::operator-=(BigInteger a)
{
    (*this) += -a;
    return *this;
}

BigInteger& BigInteger::operator*=(BigInteger a)
{
    (*this) = (*this) * a;
    return *this;
}

BigInteger& BigInteger::operator/=(BigInteger a)
{
    if (!a) {
        throw "Division by zero!";
    }

    (*this) = (*this) / a;
    return *this;
}

BigInteger& BigInteger::operator%=(BigInteger a)
{
    if (!a) {
        throw "Divivsion by zero!";
    }

    (*this) = (*this) % a;
    return (*this);
}

BigInteger& BigInteger::operator=(BigInteger a)
{
    _isNegative = a._isNegative;
    _digits = a._digits;
    return *this;
}

BigInteger BigInteger::operator+(BigInteger a) const
{
    BigInteger tmp = (*this);
    tmp += a;
    return tmp;
}

BigInteger BigInteger::operator-(BigInteger a) const
{
    BigInteger tmp = (*this);
    tmp -= a;
    return tmp;
}

BigInteger BigInteger::operator*(BigInteger a) const
{
    BigInteger ans = 0;

    for (int i = 0; i < a._digits.size(); ++i) {
        BigInteger tmp;
        tmp._digits.resize(_digits.size() + i);
        int p = 0;

        for (int j = 0; j < _digits.size(); ++j) {
           tmp._digits[j + i] = _digits[j] * a._digits[i] + p;
           p = tmp._digits[j + i] / 10;
           tmp._digits[j + i] %= 10;
        }

        if (p > 0) {
            tmp._digits.push_back(p);
        }

        tmp.normalize();
        ans += tmp;
    }

    if ((*this)._isNegative == a._isNegative) {
        ans._isNegative = false;
    }
    else {
        ans._isNegative = true;
    }

    ans.normalize();
    return ans;
}

BigInteger BigInteger::operator/(BigInteger a) const
{
    if (!a) {
        throw "Division by zero!";
    }

    BigInteger tmp = 0;
    BigInteger quotient = 0;

    if ((*this)._isNegative == a._isNegative) {
        quotient._isNegative = false;
    }
    else {
        quotient._isNegative = true;
    }

    int ind = _digits.size() - 1;
    a = abs(a);

    while (ind >= 0) {
        tmp = tmp * 10 + _digits[ind];

        if (tmp < a) {
            quotient._digits.push_back(0);
        }
        else {
            int m = 1;

            while (a * m <= tmp) {
                ++m;
            }

            --m;

            tmp -= a * m;
            quotient._digits.push_back(m);
        }

        --ind;
    }

    reverse(quotient._digits.begin(), quotient._digits.end());
    quotient.normalize();

    if ((*this)._isNegative && tmp != 0) {
        if (quotient._isNegative) {
            --quotient;
        }
        else {
            ++quotient;
        }
    }

    return quotient;
}

BigInteger BigInteger::operator%(BigInteger a) const
{
    if (!a) {
        throw "Division by zero!";
    }

    BigInteger tmp = (*this) - ((*this) / a) * a;
    return tmp;
}

BigInteger BigInteger::operator-()
{
    BigInteger tmp = (*this);
    tmp._isNegative = !_isNegative;

    if (_digits.size() == 1 && _digits[0] == 0) {
        tmp._isNegative = false;
    }

    return tmp;
}

BigInteger& BigInteger::operator++()
{
    if (!_isNegative) {
        ++_digits[0];
        int p = _digits[0] / 10;
        _digits[0] %= 10;

        for (size_t i = 1; i < _digits.size() && p > 0; ++i) {
            ++_digits[i];
            p = _digits[i] / 10;
            _digits[i] %= 10;
        }

        if (p > 0) {
            _digits.push_back(1);
        }
    }
    else {
        --_digits[0];
        int p = (int)(_digits[0] < 0);
        _digits[0] = (_digits[0] + 10) % 10;

        for (size_t i = 1; i < _digits.size() && p > 0; ++i) {
            --_digits[i];
            p = (int)(_digits[i] < 0);
            _digits[i] = (_digits[i] + 10) % 10;
        }
    }

    (*this).normalize();
    return *this;
}

BigInteger& BigInteger::operator--()
{
    if (_isNegative) {
        ++_digits[0];
        int p = _digits[0] / 10;
        _digits[0] %= 10;

        for (size_t i = 1; i < _digits.size() && p > 0; ++i) {
            ++_digits[i];
            p = _digits[i] / 10;
            _digits[i] %= 10;
        }

        if (p > 0) {
            _digits.push_back(1);
        }
    }
    else {
        if (_digits.size() == 0 && _digits[0] == 0) {
            _digits[0] = 1;
            _isNegative = true;
        }
        else {
            --_digits[0];
            int p = (int)(_digits[0] < 0);
            _digits[0] = (_digits[0] + 10) % 10;

            for (size_t i = 1; i < _digits.size() && p > 0; ++i) {
                --_digits[i];
                p = (int)(_digits[i] < 0);
                _digits[i] = (_digits[i] + 10) % 10;
            }
        }
    }

    (*this).normalize();
    return *this;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger tmp = *this;
    ++(*this);
    return tmp;
}

BigInteger BigInteger::operator--(int)
{
    BigInteger tmp = *this;
    --(*this);
    return tmp;
}

void swap(BigInteger & a,BigInteger & b)
{
    BigInteger tmp = a;
    a = b;
    b = tmp;
}

bool operator==(const BigInteger& a, const BigInteger& b)
{
    return !(a < b) && !(b < a);
}

bool operator!=(const BigInteger& a, const BigInteger& b)
{
    return (a < b) || (b < a);
}

bool operator<(const BigInteger& a, const BigInteger& b)
{
    if (a._isNegative && !b._isNegative) {
        return true;
    }
    else if (!a._isNegative && b._isNegative) {
        return false;
    }

    bool flag = false;

    if (a._digits.size() < b._digits.size()) {
        flag = true;
    }
    else if (a._digits.size() > b._digits.size()) {
        flag = false;
    }
    else {
        int ind = a._digits.size() - 1;

        while (ind > 0 && a._digits[ind] == b._digits[ind]) {
            --ind;
        }

        flag = (a._digits[ind] < b._digits[ind]);

        if (ind == 0 && a._digits[ind] == b._digits[ind]) {
            return false;
        }
    }

    if (a._isNegative) {
        return !flag;
    }

    return flag;
}

bool operator<=(const BigInteger& a, const BigInteger& b)
{
    return (a < b) || (a == b);
}

bool operator>(const BigInteger& a, const BigInteger& b)
{
    return b < a;
}

bool operator>=(const BigInteger& a, const BigInteger& b)
{
    return (b < a) || (b == a);
}

string BigInteger::toString() const
{
    string res;

    if (_isNegative) {
        res.push_back('-');
    }

    for (int i = _digits.size() - 1; i >= 0; --i) {
        res.push_back(_digits[i] + '0');
    }

    return res;
}

BigInteger::operator bool() const
{
    if (_digits.size() == 1 && _digits[0] == 0) {
        return false;
    }

    return true;
}

std::istream& operator>>(std::istream& sin, BigInteger& num)
{
    string s;
    sin >> s;
    num = BigInteger(s);
    return sin;
}

std::ostream& operator<<(std::ostream& sout,const BigInteger& num)
{
    string s = num.toString();
    sout << s;
    return sout;
}

BigInteger abs(BigInteger a)
{
    a._isNegative = false;
    return a;
}