#include "Complex.h"
#include <iostream>
#include <stdio.h>
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
Complex::Complex(Complex const &obj)
{
    a=obj.a;
    b=obj.b;
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
Complex::Complex(Fraction const &r, Fraction const &i )
{
    a = r;
    b = i;
}
Complex Complex::operator + (Complex const &obj)
{
    Fraction f1(0,1);
    Complex res(f1,f1);
    res.a = a + obj.a;
    res.b = b + obj.b;
    return res;
}
Complex Complex::operator * (Complex const &obj)
{
    Fraction f1(0,1);
    Complex res(f1,f1);
    res.a = a * obj.a+(b * obj.b)*(-1);
    res.b = a* obj.b +b*obj.a;
    return res;
}
Complex Complex::operator / (Complex const &other)
{

    float num=sqrt(pow(other.a.getfloat(),2)+pow(other.b.getfloat(),2));
    Complex cc(*this);
    float f=1/num;
    Complex n(cc*other.conjugue());
    //cout<<" 1/f="<<(1/f)<<"division:"<<other<<" soit "<<(n*f)<<endl;
    return n*f;

}
Complex Complex::operator * (float const &scalar)
{
    Fraction f1(0,1);
    Complex res(f1,f1);
    res.a = a * scalar;
    res.b = b*scalar;
    return res;
}
Complex Complex::operator * (int const &scalar)
{

    Fraction f1(0,1);
    Complex res(f1,f1);
    res.a = a * scalar;
    res.b = b*scalar;
    return res;
}

float Complex::module()
{
    return sqrt(pow(a.getfloat(),2)+pow(b.getfloat(),2));
}
Complex Complex::conjugue() const
{
    Fraction f1(a);
    Fraction f2(b);
    f2=f2*-1;
    Complex x(f1,f2);
    return x;
}
