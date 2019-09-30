#ifndef COMPLEX_H
#define COMPLEX_H

#include "Fraction.h"
#include <ostream>
#include <list>
#include <iterator>
#include <vector>
// complex made of 2 fractions
// a+ bi
class Complex
{
private:
    Fraction a; // reelle, real
    Fraction b; // imaginaire, imaginary

public:
    Complex() ;
    Complex(Fraction  const &cr, Fraction const &i) ;
    Complex(Complex const &obj) ;
    Complex operator + (Complex const &obj);
    Complex operator * (Complex const &obj);
    Complex operator * (int const &scalar);
    Complex operator * (float const &scalar);
    bool operator != (Complex const &obj);
    Complex operator / (Complex const &other);
    bool iszero() const
    {
        return a.iszero()&&b.iszero();
    };
    float module();
    Complex conjugue() const;
    friend std::ostream& operator<<(std::ostream&, const Complex&);

};

#endif // COMPLEX_H
