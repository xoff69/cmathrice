#ifndef COMPLEX_H
#define COMPLEX_H

#include "Fraction.h"
#include <ostream>
#include <list>
#include <iterator>
#include <vector>

class Complex
{
private:
    Fraction a; // reelle
    Fraction b; // imaginaire

public:
    Complex(Fraction r , Fraction i) ;
    Complex operator + (Complex const &obj);
    Complex operator * (Complex const &obj);
    Complex operator * (int const scalar);

    float module();

    friend std::ostream& operator<<(std::ostream&, const Complex&);

};

#endif // COMPLEX_H
