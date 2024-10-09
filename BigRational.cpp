#include "BigRational.h"

BigInteger gcd(BigInteger a, BigInteger b)
{
    return (b == 0 ? a : gcd(b, a % b));
}

bool operator<(const BigRational & a,const BigRational b)
{
    if (!a._isNegative && b._isNegative) {
        return false;
    }
    else if (a._isNegative && !b._isNegative) {
        return true;
    }
    else {
        BigInteger c = a._num * b._denom, d = b._num * a._denom;

        if (a._isNegative) {
            return c > d;
        }
        else {
            return c < d;
        }
    }
}

bool operator<=(const BigRational & a,const BigRational b)
{
    return a < b || a == b;
}

bool operator>(const BigRational & a,const BigRational b)
{
    return b < a;
}

bool operator>=(const BigRational & a,const BigRational b)
{
    return b < a || b == a;
}

bool operator==(const BigRational & a,const BigRational b)
{
    return !(a < b) && !(b < a);
}

bool operator!=(const BigRational & a,const BigRational b)
{
    return a < b || b < a;
}

std::istream& operator>>(std::istream& in, BigRational& a)
{
    a = 0;
    string s;
    in >> s;

    if (s[0] == '-') {
        a._isNegative = true;
        s = s.substr(1);
    }
    else {
        a._isNegative = false;
    }

    if (s.find('.') == std::string::npos) {
        a._denom = 1;
        BigInteger p = 1;

        for (int i = s.size() - 1; i >= 0; --i) {
            a._num += p * (s[i] - '0');
            p *= 10;
        }

        a.reduce();
    }
    else {
        int pos = s.find('.');
        BigInteger p = 1;
        a._denom = 1;

        for (int i = pos - 1; i >= 0; --i) {
            a._num += p * (s[i] - '0');
            p *= 10;
        }

        for (int i = pos + 1; i < s.size(); ++i) {
            a._num = a._num * 10 + (s[i] - '0');
            a._denom *= 10;
        }

        a.reduce();
    }

    return in;
}

void BigRational::reduce()
{
    BigInteger g = gcd(_num, _denom);
    _num /= g;
    _denom /= g;

    if (_num < 0) {
        _isNegative = !_isNegative;
        _num = -_num;
    }

    if (_denom < 0) {
        _isNegative = !_isNegative;
        _denom = -_denom;
    }

    if (_num == 0) {
        _isNegative = false;
    }
}

BigRational::BigRational(BigInteger a)
{
    _denom = 1;
    _num = abs(a);

    if (a < 0) {
        _isNegative = true;
    }
    else {
        _isNegative = false;
    }
}

BigRational::BigRational(BigInteger num,BigInteger denom)
{
    if (denom == 0) {
        throw "Division by zero!";
    }

    _num = num;
    _denom = denom;
    this->reduce();
}

BigRational::BigRational(int a)
{
    _num = BigInteger(a);
    _denom = 1;
    this->reduce();
}

BigRational BigRational::operator+(BigRational a) const
{
    BigRational res = (*this);
    res += a;
    return res;
}

BigRational BigRational::operator-(BigRational a) const
{
    BigRational res = (*this);
    res -= a;
    return res;
}

BigRational BigRational::operator*(BigRational a) const
{
    BigRational res = (*this);
    res *= a;
    return res;
}

BigRational BigRational::operator/(BigRational a) const
{
    BigRational res = (*this);
    res /= a;
    return res;
}

BigRational & BigRational::operator+=(BigRational a)
{
    if (_isNegative == a._isNegative) {
        _num = (_num * a._denom + a._num * _denom);
    }
    else {
        _num = (_num * a._denom - a._num * _denom);
    }

    _denom = _denom * a._denom;
    this->reduce();
    return (*this);
}

BigRational & BigRational::operator-=(BigRational a)
{
    (*this) += -a;
    return (*this);
}

BigRational & BigRational::operator*=(BigRational a)
{
    _num *= a._num;
    _denom *= a._denom;
    this->reduce();
    return (*this);
}

BigRational & BigRational::operator/=(BigRational a)
{
    if (a._num == 0) {
        throw "Division by zero!";
    }

    _num *= a._denom;
    _denom *= a._num;
    this->reduce();
    return(*this);
}

BigRational BigRational::operator-() const
{
    BigRational res = *this;
    res._isNegative = !res._isNegative;
    return res;
}

BigRational::operator double() const
{
    double res = 0;
    int precision = 0;

    if (_num / _denom > 0) {
        string tmp = (_num / _denom).toString();

        for (size_t i = 0; i < tmp.size(); ++i) {
            res *= 10;

            if (precision < 16) {
                res += tmp[i] - '0';
                ++precision;
            }
        }
    }

    BigInteger reminder = _num % _denom;
    int cnt = 0;

    for (size_t i = precision; i < 16 && reminder > 0; ++i) {
        reminder *= 10;
        res = res * 10 + (reminder / _denom).toString()[0] - '0';
        reminder %= _denom;
        ++cnt;
    }

    for (size_t i = 0; i < cnt; ++i) {
        res /= 10;
    }

    return res;
}

BigRational::operator bool() const
{
    return (_num == 0);
}

string BigRational::toString() const
{
    string res;

    if (_isNegative) {
        res.push_back('-');
    }

    res += _num.toString();
    res += " / ";
    res += _denom.toString();

    return res;
}

string BigRational::asDecimal(size_t precision) const
{
    string res;

    if (_isNegative) {
        res.push_back('-');
    }

    res += (_num / _denom).toString();

    BigInteger reminder = _num % _denom;

    if (precision > 0) {
        res.push_back('.');

        for (size_t i = 0; i < precision; ++i) {
            reminder *= 10;
            res += (reminder / _denom).toString();
            reminder %= _denom;
        }
    }

    return res;
}