#ifndef BIGINTEGER_HPP
#define BIGINTEGER_HPP

#include <iostream>
#include <cstring>
#include <vector>

class BigInteger
{
private:
    std::string digit;
    bool isNegative{false};

public:
    // Constructors
    BigInteger() = default;
    BigInteger(std::string &str);
    BigInteger(const char *ch);
    BigInteger(unsigned long long int num);
    BigInteger(const BigInteger &bigint);

    // Assignment operator overloading
    BigInteger &operator=(const BigInteger &bigint);
    BigInteger &operator=(std::string &str);
    BigInteger &operator=(const char *ch);
    BigInteger &operator=(unsigned long long int num);

    // Pre Operator
    BigInteger &operator++();
    BigInteger &operator--();
    // Post Operator
    BigInteger operator++(int tmp);
    BigInteger operator--(int tmp);

    bool getIsNegative() const { return isNegative; }
    void setIsNegative(bool isNegative_) { isNegative = isNegative_; }
    std::string getDigit() const { return digit; }
    void setDigit(const std::string &digit_) { digit = digit_; }

    // Addition and Subtraction

    friend BigInteger &operator+=(BigInteger &bigint1, const BigInteger &bigint2);
    friend BigInteger operator+(const BigInteger &bigint1, const BigInteger &bigint2);
    friend BigInteger &operator-=(BigInteger &bigint1, const BigInteger &bigint2);
    friend BigInteger operator-(const BigInteger &bigint1, const BigInteger &bigint2);

    // Comparison Functions
    friend bool operator==(const BigInteger &a, const BigInteger &b);
    friend bool operator!=(const BigInteger &a, const BigInteger &b);
    friend bool operator>(const BigInteger &a, const BigInteger &b);
    friend bool operator>=(const BigInteger &a, const BigInteger &b);
    friend bool operator<(const BigInteger &a, const BigInteger &b);
    friend bool operator<=(const BigInteger &a, const BigInteger &b);

    // Multiplication and Division
    friend BigInteger &operator*=(BigInteger &, const BigInteger &);
    friend BigInteger operator*(const BigInteger &, const BigInteger &);
    friend BigInteger &operator/=(BigInteger &, const BigInteger &);
    friend BigInteger operator/(const BigInteger &, const BigInteger &);

    // Input & Output
    friend std::ostream &operator<<(std::ostream &, const BigInteger &);
    friend std::istream &operator>>(std::istream &, BigInteger &);

    // Helper Functions
    friend void divide_by_2(BigInteger &a);
    friend bool Null(const BigInteger &);
    friend int Length(const BigInteger &);
    int operator[](const int)const;

    // Others
    friend BigInteger NthCatalan(int n);
    friend BigInteger NthFibonacci(int n);
    friend BigInteger Factorial(int n);
};
BigInteger NthFibonacci(int n);
BigInteger NthCatalan(int n);
BigInteger Factorial(int n);


#endif // BIGINTEGER_HPP
