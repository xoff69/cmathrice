#ifndef FRACTION_H
#define FRACTION_H

#include <ostream>
#include <list>
#include <iterator>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <sstream>

#include <algorithm>

using namespace std;

class Fraction
{
private:
    int numerateur;
    int denominateur;

public:
    Fraction(int n = 0, int d =1);
    Fraction operator + (Fraction const &obj);
    Fraction operator * (Fraction const &obj);
    Fraction operator * (int const &obj)
    {
        if (obj!=0)
            return Fraction(numerateur*obj,denominateur);
        return Fraction(0,1);
    };
    bool operator != (Fraction const &obj);
    friend std::ostream& operator<<(std::ostream&, const Fraction&);
    Fraction operator / (Fraction const &other);
    // getter
    int getNumerateur() const
    {
        return numerateur;
    };
    int getDenominateur() const
    {
        return denominateur;
    };
    // return true if fraction =0
    bool iszero() const
    {
        return numerateur==0;
    };
    // return float representation of the fraction
    float getfloat() const
    {
        return (float) numerateur/denominateur;
    };
    // simplify Fraction
    Fraction simplify () const;
protected:


};

#endif // FRACTION_H
