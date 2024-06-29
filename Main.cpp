#include "BigInteger.hpp"

int main()
{
    BigInteger first("12345");
    std::cout << "The number of digits"
         << " in first big integer = "
         << Length(first) << '\n';
    BigInteger second(12345);
    if (first == second) {
        std::cout << "first and second are equal!\n";
    }
    else
        std::cout << "Not equal!\n";
    BigInteger third("10000");
    BigInteger fourth("100000");
    if (third < fourth) {
        std::cout << "third is smaller than fourth!\n";
    }
    BigInteger fifth("10000000");
    if (fifth > fourth) {
        std::cout << "fifth is larger than fourth!\n";
    }
 
    // Printing all the numbers
    std::cout << "first = " << first << '\n';
    std::cout << "second = " << second << '\n';
    std::cout << "third = " << third << '\n';
    std::cout << "fourth = " << fourth<< '\n';
    std::cout << "fifth = " << fifth<< '\n';
 
    // Incrementing the value of first
    first++;
    std::cout << "After incrementing the"
         << " value of first is : ";
    std::cout << first << '\n';
    BigInteger sum;
    sum = (fourth + fifth);
    std::cout << "Sum of fourth and fifth = "
         << sum << '\n';
    BigInteger product;
    product = second * third;
    std::cout << "Product of second and third = "
         << product << '\n';
 
    // Print the fibonacci number from 1 to 100
    std::cout << "-------------------------Fibonacci"
         << "------------------------------\n";
    for (int i = 0; i <= 100; i++) {
        BigInteger Fib;
        Fib = NthFibonacci(i);
        std::cout << "Fibonacci " << i << " = " << Fib<<'\n';
    }
    std::cout << "-------------------------Catalan"
         << "------------------------------\n";
    for (int i = 0; i <= 100; i++) {
        BigInteger Cat;
        Cat = NthCatalan(i);
        std::cout << "Catalan " << i << " = " << Cat<<'\n';
    }
 
    // Calculating factorial of from 1 to 100
    std::cout << "-------------------------Factorial"
         << "------------------------------\n";
    for (int i = 0; i <= 100; i++) {
        BigInteger fact;
        fact = Factorial(i);
        std::cout << "Factorial of "
             << i << " = ";
        std::cout << fact << '\n';
    }
}