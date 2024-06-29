#include "BigInteger.hpp"

//--------------------------Constructor-------------------------------------
BigInteger::BigInteger(std::string &str)
{
    int s = str.size();
    if (s == 0)
    {
        throw std::runtime_error("Empty string passed to BigInteger constructor");
    }
    this->isNegative = (str[0] == '-') ? true : false;
    int start = (str[0] == '-') ? 1 : 0;

    for (int i = s - 1; i >= start; i--)
    {
        if (isdigit(str[i]))
        {
            this->digit.push_back(str[i] - '0');
        }
        else
        {
            throw std::runtime_error("Number contains non-digit character\n");
        }
    }
}

BigInteger::BigInteger(const char *ch)
{
    int s = strlen(ch);
    if (s == 0)
    {
        throw std::runtime_error("Empty string passed to BigInteger constructor");
    }
    this->isNegative = (ch[0] == '-') ? true : false;

    int start = (ch[0] == '-') ? 1 : 0;

    for (int i = s - 1; i >= start; i--)
    {
        if (isdigit(ch[i]))
        {
            digit.push_back(ch[i] - '0');
        }
        else
        {
            throw std::runtime_error("Number contains some alphabet/special symbol\n");
        }
    }
}

BigInteger::BigInteger(unsigned long long int num)
{
    if (num < 0)
    {
        this->isNegative = true;
    }

    while (num != 0)
    {
        digit.push_back(num % 10);
        num = num / 10;
    }
}

BigInteger::BigInteger(const BigInteger &biginteBigInteger)
{
    this->digit = biginteBigInteger.digit;
    this->isNegative = biginteBigInteger.isNegative;
}

//--------------------------Assignment-------------------------------------
BigInteger &BigInteger::operator=(const BigInteger &biginteBigInteger)
{
    if (&biginteBigInteger != this)
    {
        this->digit = biginteBigInteger.digit;
        this->isNegative = biginteBigInteger.isNegative;
    }
    return *this;
}

BigInteger &BigInteger::operator=(std::string &str)
{
    BigInteger biginteBigInteger(str);
    *this = biginteBigInteger;
    return *this;
}

BigInteger &BigInteger::operator=(const char *ch)
{
    BigInteger biginteBigInteger(ch);
    *this = biginteBigInteger;
    return *this;
}

BigInteger &BigInteger::operator=(unsigned long long int num)
{
    BigInteger biginteBigInteger(num);
    *this = biginteBigInteger;
    return *this;
}

//--------------------------Pre/Post increment-------------------------------------
BigInteger &BigInteger::operator++()
{
    // Pre Increment

    int n = digit.size();
    int i;
    for (i = 0; i < n && digit[i] == 9; i++)
    {
        digit[i] = 0;
    }

    if (i == n)
    {
        digit.push_back('1');
    }
    else
    {
        digit[i]++;
    }

    return *this;
}

BigInteger BigInteger::operator++(int tmp)
{
    // Post Increment
    BigInteger TempBigInteger;
    TempBigInteger = *this;
    ++(*this);

    return TempBigInteger;
}

BigInteger &BigInteger::operator--()
{
    // Pre Decrement
    int n = digit.size();
    if (digit.size() == 1 && digit[0] == 0)
    {
        digit[0] = 1;
        isNegative = true;
        return *this;
    }

    if (isNegative)
    {
        (*this)++;

        return *this;
    }

    int i;
    for (i = 0; i < n && digit[i] == 0; i++)
    {
        digit[i] = 9;
    }
    digit[i]--;

    if (n > 1 && digit[n - 1] == 0)
    {
        digit.pop_back();
    }

    return *this;
}

BigInteger BigInteger::operator--(int tmp)
{
    // Pre Decrement
    BigInteger TempBigInteger;
    TempBigInteger = *this;
    --(*this);

    return TempBigInteger;
}



//--------------------------Addition & Subtraction-------------------------------------
BigInteger &operator+=(BigInteger &a, const BigInteger &b)
{
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if (m > n)
        a.digit.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n; i++)
    {
        if (i < m)
            s = (a.digit[i] + b.digit[i]) + t;
        else
            s = a.digit[i] + t;
        t = s / 10;
        a.digit[i] = (s % 10);
    }
    if (t)
        a.digit.push_back(t);
    return a;
}
BigInteger operator+(const BigInteger &a, const BigInteger &b)
{
    BigInteger temp;
    temp = a;
    temp += b;
    return temp;
}

BigInteger &operator-=(BigInteger &a, const BigInteger &b)
{
    //     if(a < b)
    //         throw("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n; i++)
    {
        if (i < m)
            s = a.digit[i] - b.digit[i] + t;
        else
            s = a.digit[i] + t;
        if (s < 0)
            s += 10,
                t = -1;
        else
            t = 0;
        a.digit[i] = s;
    }
    while (n > 1 && a.digit[n - 1] == 0)
        a.digit.pop_back(),
            n--;
    return a;
}
BigInteger operator-(const BigInteger &a, const BigInteger &b)
{
    BigInteger temp;
    temp = a;
    temp -= b;
    return temp;
}

//--------------------------Equality Check-------------------------------------
bool operator==(const BigInteger &a, const BigInteger &b)
{
    return a.digit == b.digit && a.isNegative == b.isNegative;
}

bool operator!=(const BigInteger &a, const BigInteger &b)
{
    return !(a == b);
}

bool operator>(const BigInteger &a, const BigInteger &b)
{
    if (a.isNegative && b.isNegative)
    {
        if (Length(a) == Length(b))
        {
            int n = Length(a);
            while (n-- > 0)
            {
                if (a.digit[n] != b.digit[n])
                {
                    return a.digit[n] < b.digit[n];
                }
            }
            return false;
        }
        else
        {
            return Length(a) < Length(b);
        }
    }
    else if (a.isNegative)
    {
        return false;
    }
    else if (b.isNegative)
    {
        return true;
    }
    else
    {

        if (Length(a) == Length(b))
        {
            int n = Length(a);
            while (n-- > 0)
            {
                if (a.digit[n] != b.digit[n])
                {
                    return a.digit[n] > b.digit[n];
                }
            }
            return false;
        }
        else
        {
            return Length(a) > Length(b);
        }
    }
}

bool operator>=(const BigInteger &a, const BigInteger &b)
{
    return a == b || a > b;
}

bool operator<(const BigInteger &a, const BigInteger &b)
{
    return !(a > b);
}

bool operator<=(const BigInteger &a, const BigInteger &b)
{
    return a == b || a < b;
}

//--------------------------Multiplication and Divison-------------------------------------
BigInteger &operator*=(BigInteger &a, const BigInteger &b)
{
    a.isNegative = (a.isNegative != b.isNegative);
    int n = a.digit.size(), m = b.digit.size();

    std::vector<int> v(n + m, 0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            v[i + j] += (a.digit[i]) * (b.digit[j]);
        }
    n += m;
    a.digit.resize(v.size());

    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digit[i] = v[i];
    }
    for (int i = n - 1; i >= 1 && !v[i]; i--)
        a.digit.pop_back();
    return a;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b)
{
    BigInteger ans;
    ans = a;
    ans *= b;
    return ans;
}

BigInteger &operator/=(BigInteger& a,const BigInteger &b){
    if(Null(b))
        throw("Arithmetic Error: Division By 0");
    if(a < b){
        a = BigInteger();
        return a;
    }
    if(a == b){
        a = BigInteger(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    std::vector<int> cat(n, 0);
    BigInteger t;
    for (i = n - 1; t * 10 + a.digit[i]  < b;i--){
        t *= 10;
        t += a.digit[i] ;
    }
    for (; i >= 0; i--){
        t = t * 10 + a.digit[i];
        for (cc = 9; cc * b > t;cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.digit.resize(cat.size());
    for (i = 0; i < lgcat;i++)
        a.digit[i] = cat[lgcat - i - 1];
    a.digit.resize(lgcat);
    return a;
}

BigInteger operator/(const BigInteger &a, const BigInteger &b)
{
    BigInteger ans;
    ans = a;
    ans /= b;
    return ans;
}

//--------------------------Output/Input Stream-------------------------------------
std::ostream &operator<<(std::ostream &out, const BigInteger &a)
{
    if (a.digit.empty())
    {
        out << "0"; // Print "0" for empty digit vector
        return out;
    }

    if (a.isNegative)
    {
        out << "-";
    }

    for (int i = a.digit.size() - 1; i >= 0; --i)
    {

        out << (short)a.digit[i];
    }

    return out;
}

std::istream &operator>>(std::istream &in,BigInteger&a){
    std::string s;
    in >> s;
    int n = s.size();
    for (int i = n - 1; i >= 0;i--){
        if(!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digit[n - i - 1] = s[i];
    }
    return in;
}

//--------------------------Helper Functions-------------------------------------
int Length(const BigInteger &a)
{
    return a.digit.size();
}

bool Null(const BigInteger& a){
    if(a.digit.size() == 1 && a.digit[0] == 0)
        return true;
    return false;
}

void divide_by_2(BigInteger & a){
    int add = 0;
    for (int i = a.digit.size() - 1; i >= 0;i--){
        int digit = (a.digit[i] >> 1) + add;
        add = ((a.digit[i] & 1) * 5);
        a.digit[i] = digit;
    }
    while(a.digit.size() > 1 && !a.digit.back())
        a.digit.pop_back();
}

int BigInteger::operator[](const int i) const
{
    if(i < 0 || i > Length(*this))
    {
        throw std::runtime_error("index out of bound\n");
    }
    return this->digit[i];
}

BigInteger sqrt(BigInteger & a){
    BigInteger left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while(left <= right){
        mid += left;
        mid += right;
        divide_by_2(mid);
        prod = (mid * mid);
        if(prod <= a){
            v = mid;
            ++mid;
            left = mid;
        }
        else{
            --mid;
            right = mid;
        }
        mid = BigInteger();
    }
    return v;
}
//--------------------------Others-------------------------------------

BigInteger NthCatalan(int n){
    BigInteger a(1),b;
    for (int i = 2; i <= n;i++)
        a *= i;
    b = a;
    for (int i = n + 1; i <= 2 * n;i++)
        b *= i;
    a *= a;
    a *= (n + 1);
    b /= a;
    return b;
}
 
BigInteger NthFibonacci(int n){
    BigInteger a(1), b(1), c;
    if(!n)
        return c;
    n--;
    while(n--){
        c = a + b;
        b = a;
        a = c;
    }
    return b;
}
 
BigInteger Factorial(int n){
    BigInteger f(1);
    for (int i = 2; i <= n;i++)
        f *= i;
    return f;
}