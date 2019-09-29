#include "Complex.h"
#include <iostream>
#include <stdio.h>      /* printf */
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <ostream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

std::ostream& operator<<(std::ostream &strm, const Complex &complex)
{
    strm<<complex.a;
    if (!complex.b.iszero())
    {
        strm<<"+"<<complex.b<<"i";
    }
    return strm;
}
Complex::Complex()
{
    Fraction f(0,1);
    a=f;
    b=f;
}
bool Complex::operator != (Complex const &obj)
{

    return a!=obj.a&&b!=obj.b;

}
Complex::Complex(Fraction r, Fraction i )
{
    a = r;
    b = i;
}
Complex Complex::operator + (Complex const &obj)
{
    Complex res(0,1);
    res.a = a + obj.a;
    res.b = b + obj.b;
    return res;
}
Complex Complex::operator * (Complex const &obj)
{
    Complex res(0,1);
    res.a = a * obj.a+(b * obj.b)*(-1);
    res.b = a* obj.b +b*obj.a;
    return res;
}
Complex Complex::operator * (int const scalar)
{
    Complex res(0,1);
    res.a = a * scalar;
    res.b = b*scalar;
    return res;
}

float Complex::module()
{
    return sqrt(pow(a.getfloat(),2)+pow(b.getfloat(),2));
}
